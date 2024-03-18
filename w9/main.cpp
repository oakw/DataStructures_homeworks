// Martins_Prokuratovs_221RDB473
// Both Week 9 and 10
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/** (Close to) as implemented in the lecture */
template <typename StackEl>
class Stack {

    public:
    vector<StackEl> data;

        void push(StackEl item) {
            this->data.push_back(item);
        }

        StackEl top() {
            return this->data.back();
        }

        StackEl pop() {
            if (this->is_empty()) {
                throw "Stack is empty";
            }

            StackEl val = this->top();
            this->data.pop_back();
            return val;
        }

        bool is_empty() {
            return this->data.empty();
        }
};

template <typename QueueEl>
class Queue {
    public:
    vector<QueueEl> data;

        void push(QueueEl item) {
            this->data.push_back(item);
        }
        QueueEl pop() {
            QueueEl val = this->data.front();
            this->data.erase(this->data.begin());
            return val;
        }
        int size() {
            return this->data.size();
        }
        bool is_empty() {
            return this->data.empty();
        }
        QueueEl top() {
            return this->data.front();
        }
};

bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9' || ch == '.';
}

int get_precedence(char ch) {
    switch(ch) {
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return -1;
    }
}

bool has_greater_or_same_precedence(char op1, char op2) {
    return get_precedence(op1) >= get_precedence(op2);
}

// Based on https://en.wikipedia.org/wiki/Shunting_yard_algorithm
// and adjustments from https://github.com/IgorAnton/Shunting-Yard/blob/main/main.cpp
Queue<string> str_to_postfix(string str) {
    Stack<char> operators;
    Queue<string> output;

    for(int i = 0 ; i < str.length() ; i++) {
        /** Put number in a queue */
        if (is_digit(str[i])) {
            string temp = "";
            while (is_digit(str[i])) {
                temp += str[i];
                i++;
            }
            i--;

            output.push(temp);

        /** Put left parenthesis in a stack */
        } else if (str[i] == '(') {
            operators.push(str[i]);

        /** Pop all operators from the stack and put them in the queue until a left parenthesis is found */
        } else if (str[i] == ')') {
            while(! operators.is_empty() && operators.top() != '(')
                output.push(string(1, operators.pop()));

            if (operators.is_empty())
                throw "Mismatched parentheses";
            else
                operators.pop();

        /** Pop all operators from the stack and put them in the queue until an operator with lower precedence is found */
        } else if (is_operator(str[i])){
            while(! operators.is_empty() && has_greater_or_same_precedence(operators.top(), str[i]))
                output.push(string(1, operators.pop()));

            operators.push(str[i]);
        }
    }

    /* Pop all remaining operators from the stack and put them in the queue */
    while (! operators.is_empty()) {
        char ch = operators.top();
        if (ch == ')')
            throw "Mismatched parentheses";

        output.push(string(1, operators.pop()));
    }

    return output;
}

/** Based on https://www.geeksforgeeks.org/evaluation-of-postfix-expression/ */
float evaluate_postfix(Queue<string> postix_tokens) {
    Stack<float> result;
    while (! postix_tokens.is_empty()) {
        string token = postix_tokens.pop();

        if (! is_operator(token[0])) {
            result.push(stof(token));

        } else {
            /** Pop two elements and apply the previously obtained operator */
            float x = result.pop();
            float y = result.pop();

            if (token == "+") 
                result.push(x + y);
            else if (token == "-")
                result.push(y - x);
            else if (token == "*")
                result.push(x * y);
            else if (token == "/")
                result.push(y / x);
        }
    }

    return result.pop();
}


int main() {
    try {
        string input;
        printf("Enter an expression: ");
        getline(cin, input);

        Queue<string> postfix = str_to_postfix(input);
        float result = evaluate_postfix(postfix);

        // Do not print trailing zeros if the result is an integer
        if (result - (int) result < 0.0001) {
            printf("Result: %d", (int) result);
        } else {
            printf("Result: %f", result);
        }

    } catch (const char* msg) {
        printf("error");
    }

    return 0;
}
