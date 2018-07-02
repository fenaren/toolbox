node () {
  stage ('Checkout') {
    deleteDir()

    checkout changelog: true, poll: true, scm:
      [$class: 'GitSCM',
      branches: [[name: env.BRANCH_NAME]],
      browser: [$class: 'GitLab',
               repoUrl: 'gitlab.dmz/leighgarbs/toolbox',
               version: '11.0'],
      extensions: [[$class: 'SubmoduleOption',
                  disableSubmodules: false,
                  parentCredentials: false,
                  recursiveSubmodules: false,
                  reference: '',
                  trackingSubmodules: false]],
      submoduleCfg: [],
      userRemoteConfigs: [[credentialsId: '',
                         url: 'http://gitlab.dmz/leighgarbs/toolbox']]]

    checkout changelog: true, poll: true, scm:
      [$class: 'GitSCM',
      branches: [[name: 'master']],
      browser: [$class: 'GitLab',
               repoUrl: 'gitlab.dmz/leighgarbs/bin',
               version: '11.0'],
      extensions: [[$class: 'RelativeTargetDirectory',
                  relativeTargetDir: '$TEMP_BIN']],
      submoduleCfg: [],
      userRemoteConfigs: [[credentialsId: '',
                         url: 'http://gitlab.dmz/leighgarbs/bin']]]

    checkout changelog: true, poll: true, scm: [$class: 'GitSCM', branches: [[name: 'master']], browser: [$class: 'GitLab', repoUrl: 'gitlab.dmz/leighgarbs/config', version: '11.0'], doGenerateSubmoduleConfigurations: true, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: '$TEMP_CONFIG']], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '', url: 'http://gitlab.dmz/leighgarbs/config']]]
  }

  stage ('cppcheck') {
    sh returnStatus: true, script: '''
      $TEMP_BIN/run-cppcheck -J --suppress=unusedFunction .
    '''
  }

  stage ('Release Unit Tests') {
    sh '''
      $TEMP_BIN/run-cmake --release .
      make unittests

      for file in unittests/*.ut; do $file; done
    '''
  }

  stage ('Debug Unit Tests') {
    sh '''
    $TEMP_BIN/run-cmake --debug .
    make unittests

    for file in unittests/*.ut; do $file; done
    '''
  }

  stage ('Valgrind') {
    step([$class: 'ValgrindBuilder', childSilentAfterFork: false, excludePattern: '', generateSuppressions: false, ignoreExitCode: false, includePattern: 'unittests/*.ut', outputDirectory: '', outputFileEnding: '.valgrind.xml', programOptions: '', removeOldReports: false, suppressionFiles: '', tool: [$class: 'ValgrindToolMemcheck', leakCheckLevel: 'full', showReachable: false, trackOrigins: true, undefinedValueErrors: true], traceChildren: false, valgrindExecutable: '', valgrindOptions: '', workingDirectory: ''])
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
