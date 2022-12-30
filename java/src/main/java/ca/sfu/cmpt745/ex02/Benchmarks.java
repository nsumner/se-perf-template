package ca.sfu.cmpt745.ex02;


import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;

import java.util.concurrent.TimeUnit;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;


@Fork(value = 1, warmups = 1)
@Warmup(iterations = 5)
@Measurement(iterations = 5)
@State(Scope.Thread)
public class Benchmarks {

    final int WORKLOAD_SIZE = 16384;
    int[] store = new int[1];
    
    OperationRunner runner = null;

    @Setup
    public void prepare() {
      // We are initializing this with a seed for determinism during testing.
      Random randoms = new Random(0x0101023L);
      List<Operation> operations = new ArrayList<Operation>(WORKLOAD_SIZE);
      for (int i = 0; i < WORKLOAD_SIZE; ++i) {
        operations.add(Operations.createOperation(randoms.nextInt(3), store));
      }
      
      runner = new OperationRunner(operations);
    }

    @Benchmark
    @BenchmarkMode(Mode.AverageTime)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public int measureRunnerPerformance() {
      runner.run();
      return store[0];
    }

}

