#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

class Node {
  private:
    Node *right_branch, *wrong_branch;
    std::string sentence;

   public:
    Node(): right_branch(NULL), wrong_branch(NULL), sentence(NULL) {};
    Node(std::string str): sentence(str) {};
    Node(std::string str, Node *right, Node *wrong): sentence(str), right_branch(right), wrong_branch(wrong) {};
    Node(std::string str, std::string right, std::string wrong): sentence(str), right_branch(new Node(right)), wrong_branch(new Node(wrong)) {};

    void setRightBranch(Node *a)      { this->right_branch = a;  }
    void setWrongBranch(Node *a)      { this->wrong_branch = a;  }
    void setSentence(std::string str) { this->sentence = str;    }

    Node *getRightBranch(void)        { return right_branch;     }
    Node *getWrongBranch(void)        { return wrong_branch;     }
    std::string getSentence(void)     { return sentence;         }

    bool isAnswer(void);

    friend std::ostream &operator<<(std::ostream &, Node &);
};

bool Node::isAnswer(void) {
  return (!right_branch && !wrong_branch);
}

std::ostream &operator<<(std::ostream &cout, Node &current_node) {
  if (current_node.isAnswer())
    std::cout << "[!] Are you thinking about: \"" << current_node.sentence << "\"\n";
  else
    std::cout << "[?] " << current_node.sentence << "\n";

  return cout;
}

#endif
