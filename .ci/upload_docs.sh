#!/bin/bash
set -e # Exit with nonzero exit code if anything fails
set -vx
SOURCE_BRANCH="master"
TARGET_BRANCH="gh-pages"

# Pull requests and commits to other branches shouldn't try to deploy, just build to verify
if [ "$TRAVIS_PULL_REQUEST" != "false" ] || [ "$TRAVIS_BRANCH" != master -a "$TRAVIS_BRANCH" != develop ]; then
    echo "No docs to upload."
    exit 0
fi

# Save some useful information
REPO=`git config remote.origin.url`
SHA=`git rev-parse --verify HEAD`

# bin.SCons happens to contain the "doc/html" tree that we want to push
# into the gh-pages branch. So we step into that directory, create a new repo,
# set the remote appropriately, then commit and push.
cd bin.SCons
git init
git config user.name "Travis CI"
git config user.email "travis-ci"

# Make sure 'GH_TOKEN' is set (as 'secure' variable) in .travis.yml
git remote add upstream "https://$GH_TOKEN@github.com/boostorg/python.git"
git fetch upstream
git reset upstream/gh-pages

# Commit the new version.
cp ../index.html .
cp ../doc/index.html doc/
git add index.html
git add doc/index.html
git add -A doc/html
git commit -m "Deploy to GitHub Pages: ${SHA}"

# Now that we're all set up, we can push.
git push -q upstream HEAD:gh-pages
