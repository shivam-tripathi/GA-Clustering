# NSGA-2 based clustering algorithm to detect communities in complex networks

#### Licencing:

These files are a part of the GA-Clustering project.

    GA-Clustering is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GA-Clustering is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GA-Clustering.  If not, see <http://www.gnu.org/licenses/>.


#### Structure:

Structure of the codebase:

./
* README.md
* data
   + Iris.csv
* src
    + utils.h
    + utils.cpp _(Base files with implementation and includes required for running of the entire software)_

    + load_data.cpp
    + load_data.h _(Files which input csv files)_

    + data.h
    + data.cpp _(Base objects for storing data loaded using above)_

    + chromosome.cpp
    + chromosome.h _(Base objects to form and store chromosomes of data)_

    + population.h
    + population.cpp _(Base objects to form a population of chromosomes)_

    + nsga2.h
    + nsga2.cpp _(NSGA2 abstract implementation)_

    + main.cpp _(main file)_

    + README.md _(This file)_



#### Trivia:

All source code resides in the src directory.

All tests (will) reside in the test directory (if written).

Presently only one data file is present, Iris.csv in the data folder.