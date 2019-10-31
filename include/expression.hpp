#pragma once
#include "parser.hpp"
#include <vector>
#include <tuple>
using std::vector;
using std::pair;

class ExpressionTable
{
public:
    ExpressionTable(Parser &parser);
    ~ExpressionTable();

    inline int get_size() const { return state_count; }
    inline vector<int> get_end_states() const { return ending_states; }
    inline char *get_data() const { return data; }

    enum class OperationType
    {
        NONE,
        CONCAT,
        OR,
        OPTIONAL,
        ONE_OR_MORE,
        ANY
    };

    struct Node
    {
        Node *parent;
        Node *left, *right;
        OperationType operation;
        vector<pair<char, char>> values;
    };

private:
    int state_count;
    vector<int> ending_states;
    char *data;

    Node *parse_expression(Parser &parser, Node *parent);
    Node *parse_sub_expression(Parser &parser, Node *parent);
    Node *parse_range(Parser &parser, Node *parent);
    Node *parse_value(Parser &parser, Node *parent, char c);
    Node *parse_unary_op(Parser &parser, Node *node);
    Node *parse_operation(Node *left, Node *right, Node *parent, OperationType op);
    Node *parse_factor(Parser &parser, Node *parent);
    Node *parse_term(Parser &parser, Node *parent);

};