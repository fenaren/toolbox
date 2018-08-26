#!groovy

@Library(value="jenkins-sl@ctest")

stages = [

  [name: 'Checkout',
   body: stageCheckout,
   args:  ["http://gitlab.dmz/leighgarbs/toolbox.git"]],

  [name: 'cppcheck',
   body: stageCppcheck,
   args: []],

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

  [name: 'Clang Static Analyzer',
   body: stageClangStaticAnalysis,
   args: []],

  [name: 'Detect GCC Warnings',
   body: stageDetectWarnings,
   args: ["GNU Make + GNU C Compiler (gcc)"]],

  [name: 'Detect Clang Warnings',
   body: stageDetectWarnings,
   args: ["Clang (LLVM based)"]]

]

doStages(stages)
