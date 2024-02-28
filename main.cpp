#include <iostream>
#include <vector>
#include <stack>
#include <string>

#define CHILDREN vector<ASTNode>

using std::string;
using std::vector;

enum class Operation {
	Add,
	Mul
};

enum class Type {
	Literal,
	Operation // Or function
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
		case Operation::Mul:
			return node.children[0].literal * node.children[1].literal;
			break;
	}

	return 0;
}

std::stack<ASTNode*> stack;
double operationed(ASTNode &node) {
	stack.push(&node);

	for (ASTNode &child : node.children){
		if (child.type == Type::Operation)
			operationed(child);
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

string result(const string &input) {
	// 1 + 2*3
	ASTNode tree(Type::Operation, Operation::Add, CHILDREN{
		ASTNode(Type::Literal, 1),
		ASTNode(Type::Operation, Operation::Mul, CHILDREN{
			ASTNode(Type::Literal, 2), ASTNode(Type::Literal, 3)
		})
	});
	std::cout << "1 + 2 * 3 = " << operationed(tree) << '\n';

	// 69 + 2 * (3 + 3)
	ASTNode tree2(Type::Operation, Operation::Add, CHILDREN{
		ASTNode(Type::Literal, 69),
		ASTNode(Type::Operation, Operation::Mul, CHILDREN{
			ASTNode(Type::Literal, 2), ASTNode(Type::Operation, Operation::Add, CHILDREN{
					ASTNode(Type::Literal, 3), ASTNode(Type::Literal, 3)
			})
		})
	});
	std::cout << "69 + 2 * (3 + 3) = " << operationed(tree2) << '\n';

	// 2 * 3
	ASTNode x = ASTNode(Type::Operation, Operation::Mul, CHILDREN{
		ASTNode(Type::Literal, 2), ASTNode(Type::Literal, 3)
	});
	std::cout << "2 * 3 = " << operationed(x) << '\n';

	return "";
}

int main() {
	std::cout << "Input: ";

	string input;
	std::getline(std::cin, input);

	std::cout << result(input) << '\n';
}
