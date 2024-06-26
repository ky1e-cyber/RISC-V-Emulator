#include "../frontend/Parser.hpp"
#include "../exceptions/RuntimeException.hpp"
#include "instructions.hpp"
#include "../consts.hpp"
#include "cassert"
#include <string>
#include <vector>

/*  Implementation of instructions   */

/*  Constructors check arguments and can throw ParserException.
    In this case, the fields have not yet been validated and a destructor is not needed. */


Add::Add(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("add", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source1_ = Parser::get_register(args[1]);
  Register source2_ = Parser::get_register(args[2]);

  dist = dist_;
  source1 = source1_;
  source2 = source2_;
}

void Add::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] + state.registers[source2];
}


Li::Li(vector<string> args) {
  // converted to types: Register, int
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException("li", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  long immediate_;
  if (Parser::is_number(args[1])) {
      immediate_ = Parser::get_immediate(args[1]);
  } else {
    throw ParserException("invalid immediate in li: " + args[1]);
  }

  dist = dist_;
  immediate = immediate_;
}

void Li::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = immediate;
}


Addi::Addi(vector<string> args) {
  // converted to types: Register, Register, int
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("addi", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source_ = Parser::get_register(args[1]);
  long immediate_;
  if (Parser::is_number(args[2])) {
      immediate_ = Parser::get_immediate(args[2]);
  } else {
    throw ParserException("invalid immediate in addi: " + args[2]);
  }

  dist = dist_;
  source = source_;
  immediate = immediate_;
}

void Addi::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source] + immediate;
}


And::And(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("and", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source1_ = Parser::get_register(args[1]);
  Register source2_ = Parser::get_register(args[2]);

  dist = dist_;
  source1 = source1_;
  source2 = source2_;
}

void And::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] & state.registers[source2];
}


Mv::Mv(vector<string> args) {
  // converted to types: Register, Register
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException("mv", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source_ = Parser::get_register(args[1]);

  dist = dist_;
  source = source_;
}

void Mv::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source];
}


Or::Or(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("or", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source1_ = Parser::get_register(args[1]);
  Register source2_ = Parser::get_register(args[2]);

  dist = dist_;
  source1 = source1_;
  source2 = source2_;
}

void Or::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] | state.registers[source2];
}


SLL::SLL(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("sll", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source1_ = Parser::get_register(args[1]);
  Register source2_ = Parser::get_register(args[2]);

  dist = dist_;
  source1 = source1_;
  source2 = source2_;
}

void SLL::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1]
                          << (state.registers[source2] & ((1 << 7) - 1));
  // Performs logical left shift on the value in register rs1 by the shift
  // amount held in the lower 5 bits of register rs2.
}

SLLI::SLLI(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("slli", args_amount, args.size());
  }

  Register dist_ = Parser::get_register(args[0]);
  Register source_ = Parser::get_register(args[1]);
  long immediate_ = Parser::get_immediate(args[2]);

  dist = dist_;
  source = source_;
  immediate = immediate_;

}

void SLLI::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = (state.registers[source] << (immediate & ((1 << 7) - 1)));
}


SRL::SRL(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("srl", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source1_ = Parser::get_register(args[1]);
  Register source2_ = Parser::get_register(args[2]);

  dist = dist_;
  source1 = source1_;
  source2 = source2_;
}

void SRL::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] =
      state.registers[source1] >> (state.registers[source2] & ((1 << 7) - 1));
  // Description: Logical right shift on the value in register rs1 by the shift
  // amount held in the lower 5 bits of register rs2
}

SRLI::SRLI(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("srli", args_amount, args.size());
  }

  Register dist_ = Parser::get_register(args[0]);
  Register source_ = Parser::get_register(args[1]);
  long immediate_ = Parser::get_immediate(args[2]);

  dist = dist_;
  source = source_;
  immediate = immediate_;

}

void SRLI::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source] >> (immediate & ((1 << 7) - 1));
}


Sub::Sub(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("sub", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source1_ = Parser::get_register(args[1]);
  Register source2_ = Parser::get_register(args[2]);

  dist = dist_;
  source1 = source1_;
  source2 = source2_;
}

void Sub::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] - state.registers[source2];
}


Xor::Xor(vector<string> args) {
  // converted to types: Register, Register, Register
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("xor", args_amount, args.size());
  }
  Register dist_ = Parser::get_register(args[0]);
  Register source1_ = Parser::get_register(args[1]);
  Register source2_ = Parser::get_register(args[2]);

  dist = dist_;
  source1 = source1_;
  source2 = source2_;
}

void Xor::exec(State &state) {
  if (dist == zero) {
    return;
  }
  state.registers[dist] = state.registers[source1] ^ state.registers[source2];
}

void Ecall::exec(State &state) { 
  if (functions.count(state.registers[a7]) == 0) {
    throw EcallException("Wrong index of ecall " + std::to_string(state.registers[a7]));
  }
  functions[state.registers[a7]](state);
}

Ecall::Ecall(vector<string> args) {
  // args amount: 0
  if (!args.empty()) {
    throw ParserException("ecall", 0, args.size());
  }
}

Call::Call(vector<std::string> args) {
  // args amount: 1
  int args_amount = 1;
  if (args.size() != args_amount) {
    throw ParserException("call", args_amount, args.size());
  }
  label = args[0];
}

void Call::exec(State &state) { 
  state.registers[ra] = state.registers[pc];
  state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
}


void Jump::exec(State &state) { state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE; }

Jump::Jump(vector<string> args) {
  int args_amount = 1;
  if (args.size() != args_amount) {
    throw ParserException("jump", args_amount, args.size());
  }
  label = args[0];
}

void JumpAndLink::exec(State &state) {
  state.registers[return_register] = state.registers[pc];
  state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
}
 
JumpAndLink::JumpAndLink(vector<string> args) {
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException("jump and link", args_amount, args.size());
  }
  Register return_register_ = Parser::get_register(args[0]);
  label = args[1];

  return_register = return_register_;
}

void BranchEqual::exec(State &state) {
  if (state.registers[first] == state.registers[second]) {
    state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
  }
}
 
BranchEqual::BranchEqual(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("branch equal", args_amount, args.size());
  }
  Register first_ = Parser::get_register(args[0]);
  Register second_ = Parser::get_register(args[1]);

  label = args[2];
  first = first_;
  second = second_;
}

void BranchEqualZero::exec(State &state) {
  if (state.registers[first] == 0) {
    state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
  }
}
 
BranchEqualZero::BranchEqualZero(vector<string> args) {
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException("branch equal", args_amount, args.size());
  }
  Register first_ = Parser::get_register(args[0]);

  label = args[1];
  first = first_;
}

void BranchNotEqual::exec(State &state) {
  if (state.registers[first] != state.registers[second]) {
    state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
  }
}
 
BranchNotEqual::BranchNotEqual(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("branch not equal", args_amount, args.size());
  }
  Register first_ = Parser::get_register(args[0]);
  Register second_ = Parser::get_register(args[1]);

  label = args[2];
  first = first_;
  second = second_;
}

void BranchLessThen::exec(State &state) {
  if (state.registers[first] < state.registers[second]) {
    state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
  }
}
 
BranchLessThen::BranchLessThen(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("branch less then", args_amount, args.size());
  }
  Register first_ = Parser::get_register(args[0]);
  Register second_ = Parser::get_register(args[1]);

  label = args[2];
  first = first_;
  second = second_;
}

void BranchGreaterEqual::exec(State &state) {
  if (state.registers[first] >= state.registers[second]) {
    state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
  }
}
 
BranchGreaterEqual::BranchGreaterEqual(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("branch greater equal", args_amount, args.size());
  }
  Register first_ = Parser::get_register(args[0]);
  Register second_ = Parser::get_register(args[1]);

  label = args[2];
  first = first_;
  second = second_;
}

BranchGreaterThen::BranchGreaterThen(vector<string> args) {
  int args_amount = 3;
  if (args.size() != args_amount) {
    throw ParserException("branch greater then", args_amount, args.size());
  }
  Register first_ = Parser::get_register(args[0]);
  Register second_ = Parser::get_register(args[1]);

  label = args[2];
  first = first_;
  second = second_;
}

void BranchGreaterThen::exec(State &state) {
  if (state.registers[first] > state.registers[second]) {
    state.registers[pc] = (state.labels[label] - 1) * INSTRUCTION_SIZE;
  }
}

void Return::exec(State &state) { state.registers[pc] = state.registers[ra]; }

Return::Return(vector<string> args) {
  int args_amount = 0;
  if (args.size() != args_amount) {
    throw ParserException("return", args_amount, args.size());
  }
}


void Sb::exec(State &state) {
  state.memory[state.registers[dst] + offset] = (std::byte) (state.registers[src] & 0xFF);
  //  SB instructions store 8-bit values from the low bits of register rs2 to memory.
}

Sb::Sb(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException("store byte", args_amount, new_args.size());
  }
  Register src_ = Parser::get_register(new_args[0]);
  Register dst_ = Parser::get_register(new_args[2]);
  long offset_ = Parser::get_immediate(new_args[1]);

  src = src_;
  dst = dst_;
  offset = offset_;

}


void Sh::exec(State & state) {
  state.memory[state.registers[dst] + offset + 3] = (std::byte) ((state.registers[src] >> 24) & 0xFF);
  state.memory[state.registers[dst] + offset + 2] = (std::byte) ((state.registers[src] >> 16) & 0xFF);
  state.memory[state.registers[dst] + offset + 1] = (std::byte) ((state.registers[src] >> 8) & 0xFF);
  state.memory[state.registers[dst] + offset] = (std::byte) (state.registers[src] & 0xFF);
  // The SH store 16-bit value from the low bits of register rs2 to memory.
}

Sh::Sh(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException("store half-word", args_amount, new_args.size());
  }
  Register src_ = Parser::get_register(new_args[0]);
  Register dst_ = Parser::get_register(new_args[2]);
  long offset_ = Parser::get_immediate(new_args[1]);

  src = src_;
  dst = dst_;
  offset = offset_;
}

void Sw::exec(State &state) {
/*
  n = 4321
  stack s
  s[0] = 1 < *10^0
  s[1] = 2 < *10^1
  s[2] = 3 < *10^2
  s[3] = 4 < *10^3
*/
  state.memory[state.registers[dst] + offset + 7] = (std::byte) ((state.registers[src] >> 56) & 0xFF);
  state.memory[state.registers[dst] + offset + 6] = (std::byte) ((state.registers[src] >> 48) & 0xFF);
  state.memory[state.registers[dst] + offset + 5] = (std::byte) ((state.registers[src] >> 40) & 0xFF);
  state.memory[state.registers[dst] + offset + 4] = (std::byte) ((state.registers[src] >> 32) & 0xFF);
  state.memory[state.registers[dst] + offset + 3] = (std::byte) ((state.registers[src] >> 24) & 0xFF);
  state.memory[state.registers[dst] + offset + 2] = (std::byte) ((state.registers[src] >> 16) & 0xFF);
  state.memory[state.registers[dst] + offset + 1] = (std::byte) ((state.registers[src] >> 8) & 0xFF);
  state.memory[state.registers[dst] + offset] = (std::byte) (state.registers[src] & 0xFF);
  // The SW, SH, and SB instructions store 64-bit, 32-bit, and 16-bit values from the low bits of register rs2 to memory.
}

Sw::Sw(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException("store word", args_amount, new_args.size());
  }
  Register src_ = Parser::get_register(new_args[0]);
  Register dst_ = Parser::get_register(new_args[2]);
  long offset_ = Parser::get_immediate(new_args[1]);

  src = src_;
  dst = dst_;
  offset = offset_;
}

void Lw::exec(State &state) {
/*
  n = 4321
  stack s
  s[0] = 1 < *10^0
  s[1] = 2 < *10^1
  s[2] = 3 < *10^2
  s[3] = 4 < *10^3
*/
  std::byte eighth = state.memory[state.registers[src] + offset];
  std::byte seventh = state.memory[state.registers[src] + offset + 1];
  std::byte sixth = state.memory[state.registers[src] + offset + 2];
  std::byte fifth = state.memory[state.registers[src] + offset + 3];
  std::byte fourth = state.memory[state.registers[src] + offset + 4];
  std::byte third = state.memory[state.registers[src] + offset + 5];
  std::byte second = state.memory[state.registers[src] + offset + 6];
  std::byte first = state.memory[state.registers[src] + offset + 7];
  state.registers[dst] = (long) ((((long) first) << 56) | (((long) second) << 48) | (((long) third) << 40) | (((long) fourth) << 32) | (((long) fifth) << 24) | (((long) sixth) << 16) | (((long) seventh) << 8) | (long) eighth);
}

Lw::Lw(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException("Load word", args_amount, new_args.size());
  }
  Register dst_ = Parser::get_register(new_args[0]);
  Register src_ = Parser::get_register(new_args[2]);
  long offset_ = Parser::get_immediate(new_args[1]);

  src = src_;
  dst = dst_;
  offset = offset_;
}

void Lh::exec(State &state) {
  std::byte fourth = state.memory[state.registers[src] + offset];
  std::byte third = state.memory[state.registers[src] + offset + 1];
  std::byte second = state.memory[state.registers[src] + offset + 2];
  std::byte first = state.memory[state.registers[src] + offset + 3];
  state.registers[dst] = (long) ((((long) first << 24)) | (long) (second) << 16 | (long) third << 8 | (long) fourth);
}

Lh::Lh(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException("Load half-word", args_amount, new_args.size());
  }

  Register dst_ = Parser::get_register(new_args[0]);
  Register src_ = Parser::get_register(new_args[2]);
  long offset_ = Parser::get_immediate(new_args[1]);

  src = src_;
  dst = dst_;
  offset = offset_;
}

void Lb::exec(State &state) {
  std::byte first = state.memory[state.registers[src] + offset];
  state.registers[dst] = (long) (first);
}

Lb::Lb(vector<string> args) {
  int args_amount = 3;
  vector<string> new_args = Parser::get_offset(args);
  if (new_args.size() != args_amount) {
    throw ParserException("Load byte", args_amount, new_args.size());
  }
  Register dst_ = Parser::get_register(new_args[0]);
  Register src_ = Parser::get_register(new_args[2]);
  long offset_ = Parser::get_immediate(new_args[1]);

  src = src_;
  dst = dst_;
  offset = offset_;
}


void La::exec(State &state) {
  state.registers[dst] = state.labels[label] * INSTRUCTION_SIZE;
}

La::La(vector<string> args) {
  int args_amount = 2;
  if (args.size() != args_amount) {
    throw ParserException("Load address", args_amount, args.size());
  }
  Register dst_ = Parser::get_register(args[0]);
  dst = dst_;
  label = args[1];
}


EBreak::EBreak(vector<string> args) {
  int args_amount = 0;
  if (args.size() != args_amount) {
    throw ParserException("Load byte", args_amount, args.size());
  }
}

void EBreak::exec(State& state) { }


Data::Data(vector<string> args) {
  assert(args.size() == 1);
  content = Parser::get_immediate(args[0]);
}

void Data::exec(State& state) {
  throw RuntimeException("DATA SECTION CANNOT BE EXECUTED");
}
