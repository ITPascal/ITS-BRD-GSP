# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard"
  "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/1"
  "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard"
  "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard/tmp"
  "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard/src/Aufgabe3.Debug+ITSboard-stamp"
  "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard/src"
  "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard/src/Aufgabe3.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard/src/Aufgabe3.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/pascalsendecky/Studium/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe3/tmp/Aufgabe3.Debug+ITSboard/src/Aufgabe3.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
