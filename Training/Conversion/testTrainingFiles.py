#!/bin/bash
import ROOT
import os
import random

rootFiles = []

filePath = "/vols/cms/mkomm/LLP/samples/rootFiles.txt"

f = open(filePath)
for l in f:
    absPath = os.path.join(filePath.rsplit('/',1)[0],l.replace("\n","").replace("\r",""))
    rootFiles.append(absPath)
f.close()

labelNames = [
    "isB","isGBB","isBB","isLeptonicB","isLeptonicB_C","isC","isGCC","isCC","isUD","isS","isG","isUndefined",
    "isFromLLgno",
    "isFromLLgno_isB","isFromLLgno_isGBB","isFromLLgno_isBB","isFromLLgno_isLeptonicB","isFromLLgno_isLeptonicB_C","isFromLLgno_isC","isFromLLgno_isGCC","isFromLLgno_isCC","isFromLLgno_isUD","isFromLLgno_isS","isFromLLgno_isG","isFromLLgno_isUndefined",
]
nJetsPerLabel = {}
for labelName in labelNames:
    nJetsPerLabel[labelName]=0

corruptedFiles = []
emptyFiles = []
nJets = 0
for ifile,rootFileName in enumerate(rootFiles):

    #print absPath
    f = ROOT.TFile(rootFileName)
    if not f or f.IsZombie():
        print "Corrupted: ",rootFileName
        corruptedFiles.append(absPath)
        continue
    tree = f.Get("deepntuplizer/tree")
    if not tree or tree.GetEntries()<10:
        print "Emptry tree?: ",rootFileName,tree
        corruptedFiles.append(absPath)
        continue
    if tree.GetEntries()<200:
        emptyFiles.append(absPath)
    print (ifile+1),"/",len(rootFiles),":",rootFileName,tree.GetEntries()
    for entry in range(tree.GetEntries()):
        tree.GetEntry(entry)
        for ilabel,labelName in enumerate(labelNames):
            if getattr(tree,labelName)>0.5:
                nJetsPerLabel[labelName]+=1
    nJets+=tree.GetEntries()
print "----------------------------"
print "corrupted files"
for f in corruptedFiles:
    print f
print "----------------------------"
print "low event files"
for f in emptyFiles:
    print f
print "----------------------------"
for ilabel,labelName in enumerate(labelNames):
    print labelName,nJetsPerLabel[labelName]
print "----------------------------"
print "Total: ",nJets," jets"



