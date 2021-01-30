package ca.sfu.cmpt745.ex02;

import java.util.List;
import java.util.Random;


class Add1 implements Operation {
  public Add1(int[] target) {
    this.target = target;
  }

  @Override
  public void run() {
    target[0] += 1;
  }
  
  int[] target;
}


class Subtract1 implements Operation {
  public Subtract1(int[] target) {
    this.target = target;
  }

  @Override
  public void run() {
    target[0] += 1;
  }
  
  int[] target;
}


class AddConstant implements Operation {
  public AddConstant(int[] target, int constant) {
    this.target = target;
    this.constant = constant;
  }

  @Override
  public void run() {
    target[0] += constant;
  }
  
  int[] target;
  int constant;
}


public final class Operations {
  public static Operation createOperation(int code, int[] store) {
    switch(code) {
      case 0: return new Add1(store);
      case 1: return new Subtract1(store);
      case 2: return new AddConstant(store, 17);
    }
    throw new IllegalArgumentException("Invalid Operation selected: " + code);
  }
}
