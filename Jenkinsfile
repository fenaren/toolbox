#!groovy

// This line specifies the shared library and commit in that shared library to
// reference for additional content.  Left of the ampersand is the name of the
// shared library as set in Jenkins "Manage Jenkins -> Configure System", and
// right of the ampsersand identifies the commit.  Branching jenkins-sl and then
// adjusting this value is useful for testing pipeline code changes.
@Library(value = "jenkins-sl@windows-support")

import stage.*

pipeline = [new Stage(this, 'TEST')]

/*    [new StageCheckout(this, 'http://gitlab.dmz/leighgarbs/tools-cpp.git'),
     new StageBuild(this, 'RELEASE BUILD', 'release', 'tests'),
     new StageTests(this, 'RELEASE TESTS'),
     new StageBuild(this, 'DEBUG BUILD', 'debug', 'tests'),
     new StageTests(this, 'DEBUG TESTS'),
     new StageValgrind(this),
     new StageClangStaticAnalysis(this),
     new StageCppcheck(this, '--suppress=unusedFunction')])

// Construct the Linux pipeline branch
pipelineBranchWindows = new PipelineBranch(
    this,
    'Windows',
    [new StageCheckout(this, 'http://gitlab.dmz/leighgarbs/tools-cpp.git')])
 */

for stage in pipeline
{
    stage.run()
}
