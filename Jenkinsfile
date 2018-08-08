def setUnstableOnShellResult =
{
  resultShell, resultUnstable ->
  if(resultShell == resultUnstable)
  {
    currentBuild.result = 'UNSTABLE'
  }
}

def saveArtifacts =
{
  sh '''
    ARTIFACTS_DIR=artifacts
    ARTIFACTS_STAGE_DIR=$ARTIFACTS_DIR/$STAGE_NAME

    mkdir -p "$ARTIFACTS_DIR"
    rm -rf "$ARTIFACTS_STAGE_DIR"
    mkdir -p "$ARTIFACTS_STAGE_DIR"
    cd workdir
    git ls-files -o --directory | xargs -n 1 -I{} cp -a --parents {} \
      "../$ARTIFACTS_STAGE_DIR"
  '''
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

def cleanUp =
{
  sh '''
    cd workdir
    git clean -x -d -f
  '''
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
                trackingSubmodules: false],
                [$class: 'RelativeTargetDirectory',
                relativeTargetDir: 'workdir']],
    submoduleCfg: [],
    userRemoteConfigs: [[credentialsId: '',
                       url: gitlabUrlToolbox]]]

  sh """
    git clone $gitlabUrlBin
  """
}

def stageCppcheck =
{
  cleanUp()

  dir('workdir')
  {
    def shellReturnStatus = sh returnStatus: true, script: '''
      ../bin/run-cppcheck -J --suppress=unusedFunction .
    '''

    setUnstableOnShellResult(shellReturnStatus, 1)

    publishCppcheck displayAllErrors: false,
                    displayErrorSeverity: true,
                    displayNoCategorySeverity: true,
                    displayPerformanceSeverity: true,
                    displayPortabilitySeverity: true,
                    displayStyleSeverity: true,
                    displayWarningSeverity: true,
                    pattern: 'cppcheck-result.xml',
                    severityNoCategory: false
  }

  saveArtifacts()
}

def stageBuildDebug =
{
  cleanUp()

  sh '''
    cd workdir
    ../bin/run-cmake --debug .
    make -B unittests
  '''

  saveArtifacts()
}

def stageBuildRelease =
{
  cleanUp()

  sh '''
    cd workdir
    ../bin/run-cmake --release .
    make -B unittests
  '''

  saveArtifacts()
}

def stageUnitTests =
{
  sh '''
    cd workdir/unittests
    ../../bin/run-unittests *.ut
  '''
}

def stageDetectWarnings =
{
  warnings canComputeNew: false,
           canResolveRelativePaths: false,
           categoriesPattern: '',
           consoleParsers: [[parserName: 'GNU Make + GNU C Compiler (gcc)']]
}

def stageValgrind =
{
  step([$class: 'ValgrindBuilder',
    childSilentAfterFork: true,
    excludePattern: '',
    generateSuppressions: false,
    ignoreExitCode: false,
    includePattern: 'workdir/unittests/*.ut',
    outputDirectory: 'workdir/unittests',
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
    workingDirectory: 'workdir/unittests'])

  step([$class: 'ValgrindPublisher',
    failBuildOnInvalidReports: true,
    failBuildOnMissingReports: true,
    failThresholdDefinitelyLost: '',
    failThresholdInvalidReadWrite: '',
    failThresholdTotal: '',
    pattern: 'workdir/unittests/*.valgrind.xml',
    publishResultsForAbortedBuilds: false,
    publishResultsForFailedBuilds: false,
    sourceSubstitutionPaths: '',
    unstableThresholdDefinitelyLost: '0',
    unstableThresholdInvalidReadWrite: '0',
    unstableThresholdTotal: '0'])

  saveArtifacts()
}

def stageClangStaticAnalysis =
{
  cleanUp()

  sh '''
    cd workdir
    scan-build ../bin/run-cmake --debug .
    scan-build -o clangScanBuildReports -v -v --use-cc clang \
      --use-analyzer=/usr/bin/clang make -B
  '''

  saveArtifacts()
}

// If two stages have the same name the Jenkins pipeline GUI breaks a bit

stages = [[name: 'Checkout',              body: stageCheckout],
          [name: 'cppcheck',              body: stageCppcheck],
          [name: 'Release Build',         body: stageBuildRelease],
          [name: 'Detect Warnings',       body: stageDetectWarnings],
          [name: 'Release Unit Tests',    body: stageUnitTests],
          [name: 'Debug Build',           body: stageBuildDebug],
          [name: 'Debug Unit Tests',      body: stageUnitTests],
          [name: 'Valgrind',              body: stageValgrind],
          [name: 'Clang Static Analyzer', body: stageClangStaticAnalysis]]

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
    for (i = 0; i < stages.size(); i++)
    {
      doStage(stages[i].name, stages[i].body)
    }
  }
}
