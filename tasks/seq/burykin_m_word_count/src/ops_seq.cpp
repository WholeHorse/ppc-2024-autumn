#include "seq/burykin_m_word_count/include/ops_seq.hpp"

using namespace std::chrono_literals;

namespace burykin_m_word_count {

bool TestTaskSequential::pre_processing() {
  internal_order_test();
  if (taskData->inputs[0] != nullptr) {
    input_ = reinterpret_cast<char*>(taskData->inputs[0]);
  } else {
    input_ = "";
  }
  word_count_ = 0;
  return true;
}

bool TestTaskSequential::validation() {
  internal_order_test();
  return (taskData->inputs_count[0] == 0 || taskData->inputs_count[0] > 0) && taskData->outputs_count[0] == 1;
}

bool TestTaskSequential::run() {
  internal_order_test();
  word_count_ = count_words(input_);
  return true;
}

bool TestTaskSequential::post_processing() {
  internal_order_test();
  reinterpret_cast<int*>(taskData->outputs[0])[0] = word_count_;
  return true;
}

bool TestTaskSequential::is_word_character(char c) {
  return std::isalpha(static_cast<unsigned char>(c)) != 0 || c == '\'';
}

int TestTaskSequential::count_words(const std::string& text) {
  int count = 0;
  bool in_word = false;

  for (char c : text) {
    if (is_word_character(c)) {
      if (!in_word) {
        count++;
        in_word = true;
      }
    } else {
      in_word = false;
    }
  }

  return count;
}

}  // namespace burykin_m_word_count
