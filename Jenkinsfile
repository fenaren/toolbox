#!groovy

// This line specifies the shared library and commit in that shared library to
// reference for additional content.  Left of the ampersand is the name of the
// shared library as set in Jenkins "Manage Jenkins -> Configure System", and
// right of the ampsersand identifies the commit.  Branching jenkins-sl and then
// adjusting this value is useful for testing pipeline code changes.
@Library(value = "jenkins-sl@lets-go-oo")

// Stages are not specific to platforms.  At a high level each stage is expected
// to be aware of the platform it's running on and adjust itself accordingly.

pipeline_linux = [

    new StageCheckout(['http://gitlab.dmz/leighgarbs/toolbox.git'])

//    new Stage('RELEASE BUILD', stageBuild, ['release', 'tests']),

//    new Stage('RELEASE TESTS', stageTests),

//    new Stage('DEBUG BUILD', stageBuild, ['debug', 'tests']),

//    new Stage('DEBUG TESTS', stageTests),

//    new Stage('VALGRIND', stageValgrind),

//    new Stage('CPPCHECK', stageCppcheck, ['--suppress=unusedFunction']),

//    new Stage('CLANG STATIC ANALYSIS', stageClangStaticAnalysis),

//    new Stage('DETECT WARNINGS', stageDetectWarnings),

]

// We now add stages to each pipeline branch depending on what is supported for
// the platform associated with that branch.  The "<<" operator is the list
// append operator in Groovy.

// This pipeline runs on Linux, and will run on Windows at some point in the
// future.

// Construct the Linux pipeine

// Run both branches
parallel Linux: {

    runPipeline(pipeline_linux, 'Linux', true)

}, Windows: {

    //runPipeline(pipelineWindows, 'Windows', true)

},
failFast: false
