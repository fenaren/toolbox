#!groovy

@Library(value="jenkins-sl@better-pipeline-stage")

// This pipeline runs on Linux, and will run on Windows at some point in the
// future.

// Construct the Linux pipeine
pipelineLinux = [

    [name: 'Checkout',
     body: stageCheckout,
     args: ["http://gitlab.dmz/leighgarbs/toolbox.git"]],

    [name: 'Release Build',
     body: stageBuild,
     args: ['release', 'tests']],

    [name: 'Release Tests',
     body: stageTests,
     args: []],

    [name: 'Debug Build',
     body: stageBuild,
     args: ['debug', 'tests']],

    [name: 'Debug Tests',
     body: stageTests,
     args: []],

    [name: 'Valgrind',
     body: stageValgrind,
     args: []],

    [name: 'cppcheck',
     body: stageCppcheck,
     args: ["--suppress=unusedFunction"]],

    [name: 'Clang Static Analyzer',
     body: stageClangStaticAnalysis,
     args: []],

    [name: 'Detect Warnings',
     body: stageDetectWarnings,
     args: []]

]

// Construct the Windows pipeline
pipelineWindows = [

    [name: 'Checkout',
     body: stageCheckout,
     args: ["http://gitlab.dmz/leighgarbs/toolbox.git"]],

    [name: 'Release Build',
     body: stageBuild,
     args: ['release', 'tests']],

    [name: 'Release Tests',
     body: stageTests,
     args: []],

    [name: 'Debug Build',
     body: stageBuild,
     args: ['debug', 'tests']],

    [name: 'Debug Tests',
     body: stageTests,
     args: []],

    [name: 'Detect Warnings',
     body: stageDetectWarnings,
     args: []]

]

// Run both branches
parallel Linux: {

    cleanWs()
    runPipeline(pipelineLinux, 'Linux')

}, Windows: {

    cleanWs()
    //runPipeline(pipelineWindows, 'Windows')

},
failFast: false
