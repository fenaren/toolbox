#!/usr/bin/env groovy

GITLAB_URL_TOOLBOX = 'http://gitlab.dmz/leighgarbs/toolbox.git'

STAGES = ['Checkout',
          'cppcheck',
          'Unit Tests - Release Build',
          'Unit Tests - Debug Build',
          'Valgrind']

properties([[$class: 'GitLabConnectionProperty',
            gitLabConnection: 'gitlab.dmz'],
            pipelineTriggers([[$class: 'GitLabPushTrigger',
                              pendingBuildName: STAGES[0]]])])

gitlabBuilds(builds: ['Checkout', 'cppcheck', 'Unit Tests - Release Build', 'Unit Tests - Debug Build', 'Valgrind]') {

node ()
{
  stage (STAGES[0])
  {
    deleteDir()

    checkout changelog: true, poll: true, scm: [$class: 'GitSCM',
      branches: [[name: env.BRANCH_NAME]],
      browser: [$class: 'GitLab',
               repoUrl: GITLAB_URL_TOOLBOX,
               version: '11.0'],
      extensions: [[$class: 'SubmoduleOption',
                  disableSubmodules: false,
                  parentCredentials: false,
                  recursiveSubmodules: false,
                  reference: '',
                  trackingSubmodules: false]],
      submoduleCfg: [],
      userRemoteConfigs: [[credentialsId: '',
                         url: GITLAB_URL_TOOLBOX]]]

    sh '''
      git clone http://gitlab.dmz/leighgarbs/bin.git $TEMP_BIN
    '''
  }

  stage (STAGES[1])
  {
    def shellReturnStatus = sh returnStatus: true, script: '''
      $TEMP_BIN/run-cppcheck -J --suppress=unusedFunction .
    '''

    if(shellReturnStatus == 1) { currentBuild.result = 'UNSTABLE' }
  }

  stage (STAGES[2])
  {
    sh '''
      $TEMP_BIN/run-cmake --release .
      make unittests

      for file in unittests/*.ut; do $file; done
    '''
  }

  stage (STAGES[3])
  {
    sh '''
      $TEMP_BIN/run-cmake --debug .
      make unittests

      for file in unittests/*.ut; do $file; done
    '''
  }

  stage (STAGES[4])
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
      workingDirectory: ''])

    step([$class: 'ValgrindPublisher',
      failBuildOnInvalidReports: false,
      failBuildOnMissingReports: false,
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

  stage ('Clang Static Analyzer')
  {
    sh '''
      rm CMakeCache.txt
      rm -rf CMakeFiles
      scan-build $TEMP_BIN/run-cmake --debug .
      scan-build -o clangScanBuildReports -v -v --use-cc clang --use-analyzer=/usr/bin/clang make
    '''
  }
}

}
