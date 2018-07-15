def setUnstableOnShellResult =
{
  resultShell, resultUnstable ->
  if(resultShell == resultUnstable)
  {
    currentBuild.result = 'UNSTABLE'
  }
}

def doStage =
{
  stageName, stageBody ->
  stage (stageName)
  {
    gitlabCommitStatus(name: stageName)
    {
      stageBody()
    }

    if (currentBuild.result == 'UNSTABLE')
    {
      updateGitlabCommitStatus(name: stageName, state: 'failed')
    }
  }
}

def stageCheckout =
{
  gitlabUrl         = 'http://gitlab.dmz/leighgarbs/'
  gitlabUrlToolbox  = gitlabUrl + 'toolbox.git'
  gitlabUrlBin      = gitlabUrl + 'bin.git'

  deleteDir()

  checkout changelog: true, poll: true, scm: [$class: 'GitSCM',
    branches: [[name: env.BRANCH_NAME]],
    browser: [$class: 'GitLab',
             repoUrl: gitlabUrlToolbox,
             version: '11.0'],
    extensions: [[$class: 'SubmoduleOption',
                disableSubmodules: false,
                parentCredentials: false,
                recursiveSubmodules: false,
                reference: '',
                trackingSubmodules: false]],
    submoduleCfg: [],
    userRemoteConfigs: [[credentialsId: '',
                       url: gitlabUrlToolbox]]]

  sh """
    git clone $gitlabUrlBin $TEMP_BIN
  """
}

def stageCppcheck =
{
  def shellReturnStatus = sh returnStatus: true, script: '''
    $TEMP_BIN/run-cppcheck -J --suppress=unusedFunction .
  '''

  setUnstableOnShellResult(shellReturnStatus, 1)
}

def stageUnitTestRelease =
{
  sh '''
    $TEMP_BIN/run-cmake --release .
    make unittests
    cd unittests

    for file in *.ut; do ./$file; done
  '''

  warnings canComputeNew: false,
           canResolveRelativePaths: false,
           categoriesPattern: '',
           consoleParsers: [[parserName: 'GNU Make + GNU C Compiler (gcc)']]
}

def stageUnitTestDebug =
{
  sh '''
    $TEMP_BIN/run-cmake --debug .
    make unittests
    cd unittests

    for file in *.ut; do ./$file; done
  '''
}

def stageValgrind =
{
  step([$class: 'ValgrindBuilder',
    childSilentAfterFork: false,
    excludePattern: '',
    generateSuppressions: false,
    ignoreExitCode: false,
    includePattern: 'unittests/*.ut',
    outputDirectory: '',
    outputFileEnding: '.valgrind.xml',
    programOptions: '',
    removeOldReports: false,
    suppressionFiles: '',
    tool: [$class: 'ValgrindToolMemcheck',
          leakCheckLevel: 'full',
          showReachable: false,
          trackOrigins: true,
          undefinedValueErrors: true],
    traceChildren: false,
    valgrindExecutable: '',
    valgrindOptions: '',
    workingDirectory: 'unittests'])

  step([$class: 'ValgrindPublisher',
    failBuildOnInvalidReports: true,
    failBuildOnMissingReports: true,
    failThresholdDefinitelyLost: '',
    failThresholdInvalidReadWrite: '',
    failThresholdTotal: '',
    pattern: '*.valgrind.xml',
    publishResultsForAbortedBuilds: false,
    publishResultsForFailedBuilds: false,
    sourceSubstitutionPaths: '',
    unstableThresholdDefinitelyLost: '0',
    unstableThresholdInvalidReadWrite: '0',
    unstableThresholdTotal: '0'])
}

def stageClangStaticAnalysis =
{
  sh '''
    rm CMakeCache.txt
    rm -rf CMakeFiles
    scan-build $TEMP_BIN/run-cmake --debug .
    scan-build -o clangScanBuildReports -v -v --use-cc clang \
      --use-analyzer=/usr/bin/clang make
  '''
}

stages = [[name: 'Checkout',                   body: stageCheckout],
          [name: 'cppcheck',                   body: stageCppcheck],
          [name: 'Unit Tests - Release Build', body: stageUnitTestRelease],
          [name: 'Unit Tests - Debug Build',   body: stageUnitTestDebug],
          [name: 'Valgrind',                   body: stageValgrind],
          [name: 'Clang Static Analyzer',      body: stageClangStaticAnalysis]]

stageNames = []
for (i = 0; i < stages.size(); i++)
{
  stageNames.plus(stages[i].name)
}

properties([[$class: 'GitLabConnectionProperty',
            gitLabConnection: 'gitlab.dmz'],
            pipelineTriggers([[$class: 'GitLabPushTrigger',
                              triggerOnPush: true,
                              triggerOnMergeRequest: true,
                              skipWorkInProgressMergeRequest: true,
                              pendingBuildName: stageNames[0]]])])

gitlabBuilds(builds: stageNames)
{
  node ()
  {
    doStage("Checkout", stageCheckout)
    doStage("cppcheck", stageCppcheck)
    doStage("Unit Tests - Release Build", stageUnitTestRelease)
    doStage("Clang Static Analyzer", stageClangStaticAnalyzer)
  }

  node ()
  {
    doStage("Checkout", stageCheckout)
    doStage("Valgrind", stageValgrind)
  }
}
