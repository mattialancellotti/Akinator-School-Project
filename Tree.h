#ifndef TREE_H
#define TREE_H

#include "Node.h"

#define EXIT  0
#define HELP  1

class Tree {
  private:
    Node *root;
    int state;

    Node *game_r(Node *);
    Node *delLeaves_r(Node *);
  public:
    Tree(): root(NULL) {};
    Tree(std::string first_sentence, std::string right_branch, std::string wrong_branch): root(new Node(first_sentence, right_branch, wrong_branch)) {};

    int getState(void);
    void game(void);
    void help(void);
    void delLeaves(void);
    void destroy(void);
};

int Tree::getState(void) {
  return state;
}

void Tree::game(void) {
  root = game_r(root);

  if (!state)
    destroy();
}

Node *Tree::game_r(Node *current_node) {
  std::string tmp;
  std::string new_question, new_answer;

  std::cout << *current_node;
  getline(std::cin, tmp);

  if (tmp == "!help") {
    help();
    std::cout << *current_node;
    getline(std::cin, tmp);
  }

  if (tmp == "!quit")
    state = EXIT;
  else if (current_node->isAnswer()) {
    if (tmp == "nope") {
      std::cout << "[?] What question should I ask you?" << std::endl;
      getline(std::cin, new_question);
      std::cout << "[?] What is the answer?" << std::endl;
      getline(std::cin, new_answer);

      current_node = new Node(new_question, new_answer, current_node->getSentence());
    } else if (tmp == "yes" || tmp == "yep"
                            || tmp == "y"
                            || tmp == "Y"
                            || tmp == "Yes"
                            || tmp == "Yep") {
      std::cout << "[@] good" << std::endl;
    } else
      std::cout << "[!] Command not recognized" << std::endl;
  } else {
    if (tmp == "yes" || tmp == "yep" 
                     || tmp == "y" 
                     || tmp == "Y"
                     || tmp == "Yes"
                     || tmp == "Yep") {
      current_node->setRightBranch(game_r(current_node->getRightBranch()));
    } else if (tmp == "nope" || tmp == "no"
                             || tmp == "n"
                             || tmp == "N"
                             || tmp == "Nope") {
      current_node->setWrongBranch(game_r(current_node->getWrongBranch()));
    } else
      std::cout << "[!] Command not recognized" << std::endl;
  }

  return current_node;
}

void Tree::help(void) {
  std::cout << "Akinator guesses your animal\n";
  std::cout << "Comands:\n\t!quit : to quit the game\n\t!help : to display di message\n";
}

void Tree::delLeaves(void) {
  root = delLeaves_r(root);
}

Node *Tree::delLeaves_r(Node *current_node) {
  if (current_node->isAnswer()) {
    delete(current_node);
    return NULL;
  } else {
    current_node->setWrongBranch(delLeaves_r(current_node->getWrongBranch()));
    current_node->setRightBranch(delLeaves_r(current_node->getRightBranch()));

    return current_node;
  }
}

void Tree::destroy(void) {
  while(root)
    delLeaves();
}

#endif
