package ca.sfu.cmpt745.ex02;

import java.util.List;
import java.util.ArrayList;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

class RunnerTests {
  @Test
  @DisplayName("Built in operations work independently")
  void
  builtInIndependent() {
    final int[] t1store = new int[1];
    final int[] t2store = new int[1];
    final int[] t3store = new int[1];
    
    List<Operation> operations = new ArrayList<Operation>();
    operations.add(Operations.createOperation(0, t1store)); // add 1
    operations.add(Operations.createOperation(1, t2store)); // subtract 1
    operations.add(Operations.createOperation(2, t3store)); // add 17
    
    OperationRunner runner = new OperationRunner(operations);
    
    runner.run();
    
    assertEquals(t1store[0], 1);
    assertEquals(t2store[0], -1);
    assertEquals(t3store[0], 17);
  }

  @Test
  @DisplayName("Built in operations work on shared data")
  void
  builtInDependent() {
    final int[] t1store = new int[1];
    
    List<Operation> operations = new ArrayList<Operation>();
    operations.add(Operations.createOperation(0, t1store)); // add 1
    operations.add(Operations.createOperation(0, t1store)); // add 1
    operations.add(Operations.createOperation(1, t1store)); // subtract 1
    operations.add(Operations.createOperation(2, t1store)); // add 17
    operations.add(Operations.createOperation(0, t1store)); // add 1
    
    OperationRunner runner = new OperationRunner(operations);
    
    runner.run();
    
    assertEquals(t1store[0], 19);
  }

  class Make42 implements Operation {
    public Make42(int[] target) {
      this.target = target;
    }

    @Override
    public void run() {
      target[0] = 42;
    }
    
    int[] target;
  }
  class Duplicate implements Operation {
    public Duplicate(int[] target) {
      this.target = target;
    }

    @Override
    public void run() {
      target[0] *= 2;
    }
    
    int[] target;
  }

  @DisplayName("New custom operations work")
  @Test
  void
  newOperations() {
    final int[] t1store = new int[1];
    
    List<Operation> operations = new ArrayList<Operation>();
    operations.add(new Make42(t1store));
    OperationRunner runner = new OperationRunner(operations);
    runner.run();
    assertEquals(t1store[0], 42);

    operations = new ArrayList<Operation>();
    operations.add(new Duplicate(t1store));
    runner = new OperationRunner(operations);
    runner.run();
    assertEquals(t1store[0], 84);
  }

  @DisplayName("Runners can run multiple times sequentially")
  @Test
  void
  multipleExecutions() {
    final int[] t1store = new int[1];
    final int[] t2store = new int[1];
    final int[] t3store = new int[1];
    
    List<Operation> operations = new ArrayList<Operation>();
    operations.add(Operations.createOperation(0, t1store)); // add 1
    operations.add(Operations.createOperation(1, t2store)); // subtract 1
    operations.add(Operations.createOperation(2, t3store)); // add 17
    
    OperationRunner runner = new OperationRunner(operations);
    
    runner.run();
    
    assertEquals(t1store[0], 1);
    assertEquals(t2store[0], -1);
    assertEquals(t3store[0], 17);
    runner.run();
    
    assertEquals(t1store[0], 2);
    assertEquals(t2store[0], -2);
    assertEquals(t3store[0], 34);
  }
}
