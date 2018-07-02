node ()
{
  stage ('toolbox - Checkout')
  {
    deleteDir()

    checkout changelog: true, poll: true, scm: [$class: 'GitSCM', branches: [[name: env.BRANCH_NAME]], browser: [$class: 'GitLab', repoUrl: 'gitlab.dmz/leighgarbs/toolbox', version: '11.0'], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '', url: 'http://gitlab.dmz/leighgarbs/toolbox']]]

    checkout changelog: true, poll: true, scm: [$class: 'GitSCM', branches: [[name: 'master']], browser: [$class: 'GitLab', repoUrl: 'gitlab.dmz/leighgarbs/bin', version: '11.0'], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: '$TEMP_BIN']], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '', url: 'http://gitlab.dmz/leighgarbs/bin']]]

    checkout changelog: true, poll: true, scm: [$class: 'GitSCM', branches: [[name: 'master']], browser: [$class: 'GitLab', repoUrl: 'gitlab.dmz/leighgarbs/config', version: '11.0'], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: '$TEMP_CONFIG']], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '', url: 'http://gitlab.dmz/leighgarbs/config']]]
  }

  stage ('toolbox - cppcheck')
  {
    sh """
    $TEMP_BIN/run-cppcheck -J --suppress=unusedFunction .
    """
  }

  stage ('toolbox - Release Unit Tests')
  {
    sh """
    $TEMP_BIN/run-cmake --release .
    make unittests

    for file in unittests/*.ut; do $file; done
    """
  }

  stage ('toolbox - Debug Unit Tests')
  {
    // Shell build step
    sh """
    $TEMP_BIN/run-cmake --debug .
    make unittests

    for file in unittests/*.ut; do $file; done
    """
  }

  stage ('toolbox - Valgrind')
  {
  }

  stage ('toolbox - Clang Static Analyzer')
  {
    sh """
    rm CMakeCache.txt
    rm -rf CMakeFiles
    scan-build $TEMP_BIN/run-cmake --debug .
    scan-build -o clangScanBuildReports -v -v --use-cc clang --use-analyzer=/usr/bin/clang make
    """
  }
}