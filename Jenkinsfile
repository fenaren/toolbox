#!groovy

// This line specifies the shared library and commit in that shared library to
// reference for additional content.  Left of the ampersand is the name of the
// shared library as set in Jenkins "Manage Jenkins -> Configure System", and
// right of the ampsersand identifies the commit.  Branching jenkins-sl and then
// adjusting this value is useful for testing pipeline code changes.
@Library(value = "jenkins-sl@filtering-bugfix")

import stage.*

// Construct the pipeline.  Stages execute in the order shown here.
def pipeline = new Pipeline(
    this,

    [new StageCheckout(
            this, 'http://gitlab.dmz/leighgarbs/tools-cpp.git', true),

     new StageBuild(this, 'DEBUG BUILD', 'debug', 'tests')])

// Run the pipeline
pipeline.run()
