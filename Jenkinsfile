#!groovy

// This line specifies the shared library and commit in that shared library to
// reference for additional content.  Left of the ampersand is the name of the
// shared library as set in Jenkins "Manage Jenkins -> Configure System", and
// right of the ampsersand identifies the commit.  Branching jenkins-sl and then
// adjusting this value is useful for testing pipeline code changes.
@Library(value = "jenkins-sl@lets-go-oo")

import stage.*

// Construct the Linux pipeline branch
pipelineBranchLinux = new PipelineBranch(
    this,
    'Linux',
    [new StageCheckout(this,
                       'http://gitlab.dmz/leighgarbs/tools-cpp.git',
                       ['http://gitlab.dmz/leighgarbs/bin.git'],
                       true),
     new StageBuild(this, 'RELEASE BUILD', 'release', 'tests'),
     new StageTests(this, 'RELEASE TESTS'),
     new StageBuild(this, 'DEBUG BUILD', 'debug', 'tests'),
     new StageTests(this, 'DEBUG TESTS'),
     new StageValgrind(this),
     new StageCppcheck(this, '--suppress=unusedFunction'),
     new StageClangStaticAnalysis(this),
     new StageDetectWarnings(this)])

// Run both branches
parallel Linux: {

    pipelineBranchLinux.run()

}, Windows: {

    //pipelineBranchWindows.run()

},
failFast: false
