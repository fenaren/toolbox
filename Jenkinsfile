#!groovy

@Library(value="jenkins-sl@master")

repoUrl = "http://gitlab.dmz/leighgarbs/toolbox.git"

branchStagesA = [

  [name: "Checkout",
   body: stageCheckout,
   args: [repoUrl]],

  [name: "cppcheck",
   body: stageCppcheck,
   args: ["--suppress=unusedFunction"]]

]

branchStagesB = [

  [name: "Checkout",
   body: stageCheckout,
   args: [repoUrl]]

  [name: "Release Build",
   body: stageBuild,
   args: ["release", "tests"]],

  [name: "Release Tests",
   body: stageTests,
   args: []]

]

branchStagesC = [

  [name: 'Checkout',
   body: stageCheckout,
   args: [repoUrl]]

  [name: "Debug Build",
   body: stageBuild,
   args: ["debug", "tests"]],

  [name: "Debug Tests",
   body: stageTests,
   args: []],

  [name: "Valgrind",
   body: stageValgrind,
   args: []]

]

branchStagesD = [

  [name: "Checkout",
   body: stageCheckout,
   args: []],

  [name: "Clang Static Analyzer",
   body: stageClangStaticAnalysis,
   args: []],

//  [name: "Detect Warnings",
//   body: stageDetectWarnings,
//   args: []]

]

parallel
branchA:
{
  //doStages(branchStagesA)
},
branchB:
{
  //doStages(branchStagesB)
},
branchC:
{
  //doStages(branchStagesC)
},
branchD:
{
  //doStages(branchStagesD)
}
