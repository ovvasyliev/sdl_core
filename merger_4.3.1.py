#! /usr/env python
import os
def execute(command):
  os.system(command)

execute("wget https://raw.githubusercontent.com/LuxoftAKutsan/sdl_core/master/branch_order.txt")
lines = file("branch_order.txt").readlines()


repos = set()
branches = []
for line in lines:
  line = line.split(":")
  uname, branch = tuple(line[0:2])
  repos.add(uname.strip())
  branches.append(uname.strip() + "/" + branch.strip())
  

execute("git remote add smartdevicelink https://github.com/smartdevicelink/sdl_core")


for repo in repos:
  execute("git remote add {} https://github.com/{}/sdl_core".format(repo,repo))

execute("git fetch smartdevicelink")
for repo in repos:
  execute("git fetch {}".format(repo))

execute("git checkout -b integration/4.3.1")
execute("git checkout integration/4.3.1")
execute("git reset --hard smartdevicelink/develop")

for branch in branches:
  execute("git merge --no-edit --no-ff {}".format(branch))
