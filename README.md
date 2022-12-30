
This is a template for some simple performance exercises using C++ and Java.

Building C++ Tasks with CMake
==============================================
1. Create a new directory for building.

        mkdir build

2. Change into the new directory.

        cd build

3. Run CMake in Release mode with the path to the source.

        cmake ../se-perf-template/c++ -DCMAKE_BUILD_TYPE=Release

4. Run make inside the build directory:

        make

By default, this should produce binaries for several test cases.
Correctness test cases reside in `out/bin/test/`.
Performance test cases reside in `out/bin/perf/`.

Note, building with a tool like ninja can be done by adding `-G Ninja` to
the cmake invocation and running ninja instead of make.

Running C++ Tests
==============================================

You can run all correctness tests automatically by simply running:

        make test

Note that this will not show you exactly which tests failed and why. You can
see this by running individual test binaries from within your build
directory, e.g.:

        out/bin/test/simple-executor

Performance tests must be manually executed, e.g.:

        out/bin/perf/executorPerf


Building Java Tasks with Maven
==============================================

1. Make the `java` directory of the template your working directory.

        cd se-performance-template/java

2. Build using maven.

        mvn clean package

Running the Java Tests
==============================================

You can run all correctness tests automatically by simply running:

        mvn test

You can run all performance tests by running:

        java -jar target/ex02-benchmarks.jar
