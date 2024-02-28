#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <math.h>

#define CHILDREN vector<ASTNode>

using std::string;
using std::vector;

enum class Operation {
	Add,
	Sub,
	Mul,
	Div,
	Pow
};

enum class Type {
	Literal,
	Operation,
	Function
};

struct ASTNode {
	Type type;
	double literal;
	Operation operation;

	vector <ASTNode> children;

	ASTNode() {}

	ASTNode(const Type &newType, double newLiteral) {
		type = newType;
		literal = newLiteral;
	}

	ASTNode(const Type &newType, const Operation &newOperation, const vector<ASTNode> &newChildren) {
		type = newType;
		operation = newOperation;
		children = newChildren;
	}
};

double performOperation(const ASTNode &node) {
	if (node.type != Type::Operation) {
		std::cerr << "Oops!\n";
		return -6969;
	}

	// Some functions may accept more than 2 parameters
	if (node.children.size() > 2){
		std::cerr << "Functions not implemented yet...\n";
		return -6969;
	}

	switch (node.operation) {
		case Operation::Add:
			return node.children[0].literal + node.children[1].literal;
			break;
		case Operation::Sub:
			return node.children[0].literal - node.children[1].literal;
			break;
		case Operation::Mul:
			return node.children[0].literal * node.children[1].literal;
			break;
		case Operation::Div:
			return node.children[0].literal / node.children[1].literal;
			break;
		case Operation::Pow:
			return std::pow(node.children[0].literal, node.children[1].literal);
			break;
	}

	return 0;
}

std::stack<ASTNode*> stack;
double evaluateAST(ASTNode &node) {
	stack.push(&node);

	for (ASTNode &child : node.children){
		if (child.type != Type::Literal)
			evaluateAST(child);
	}

	while (!stack.empty()) {
		ASTNode *n = stack.top();

		double value = performOperation(*n);
		n->type = Type::Literal;
		n->literal = value;

		stack.pop();
	}

	return node.literal;
}

// TODO:
/*ASTNode parseIntoAST(const string &input) {
	
}*/

string result(const string &input) {
	// 1 + 2*3
	ASTNode tree(Type::Operation, Operation::Add, CHILDREN{
		ASTNode(Type::Literal, 1),
		ASTNode(Type::Operation, Operation::Mul, CHILDREN{
			ASTNode(Type::Literal, 2), ASTNode(Type::Literal, 3)
		})
	});
	std::cout << "1 + 2 * 3 = " << evaluateAST(tree) << '\n';

	// 69 + 2 * (3 + 3)
	ASTNode tree2(Type::Operation, Operation::Add, CHILDREN{
		ASTNode(Type::Literal, 69),
		ASTNode(Type::Operation, Operation::Mul, CHILDREN{
			ASTNode(Type::Literal, 2), ASTNode(Type::Operation, Operation::Add, CHILDREN{
					ASTNode(Type::Literal, 3), ASTNode(Type::Literal, 3)
			})
		})
	});
	std::cout << "69 + 2 * (3 + 3) = " << evaluateAST(tree2) << '\n';

	// 2 * 3
	ASTNode x = ASTNode(Type::Operation, Operation::Mul, CHILDREN{
		ASTNode(Type::Literal, 2), ASTNode(Type::Literal, 3)
	});
	std::cout << "2 * 3 = " << evaluateAST(x) << '\n';

	ASTNode y = ASTNode(Type::Operation, Operation::Pow, CHILDREN{
		ASTNode(Type::Literal, 2), ASTNode(Type::Literal, 10)
	});
	std::cout << "2 ^ 10 = " << evaluateAST(y) << '\n';

	return "";
}

int main() {
//	std::cout << "Input: ";

	string input;
//	std::getline(std::cin, input);

	std::cout << result(input) << '\n';
}
