# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard"
  "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/1"
  "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard"
  "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/tmp"
  "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp"
  "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src"
  "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "Z:/TI_Labor/GS/Praktikum/ITS-BRD-GSP/Programs/Aufgabe1/tmp/Aufgabe1.Debug+ITSboard/src/Aufgabe1.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
