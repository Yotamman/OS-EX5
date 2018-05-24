//
// Created by Ben on 23/05/2018.
//

#include "Node.h"

Node::Node(Task *task) {
    this->task=task;
    this->next=NULL;
}

Node *Node::getNext() const {
    return next;
}

void Node::setNext(Node *next) {
    Node::next = next;
}

Task *Node::getTask() const {
    return task;
}

void Node::setTask(Task *task) {
    Node::task = task;
}

