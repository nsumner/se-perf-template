package ca.sfu.cmpt745.ex02;

import java.util.List;
import java.util.ArrayList;


public final class OperationRunner {
  OperationRunner(List<Operation> operations) {
    this.operations = new ArrayList<Operation>(operations);
  }
  
  public final void run() {
    for (Operation op : this.operations) {
      op.run();
    }
  }

  List<Operation> operations;
}

