#include <iostream>
#include <vector>
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
	bool isRootNode = false;
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

void printGivenLevel(ASTNode &node, int level) {
//	double ret = performOperation(node);

//	std::cout << "printGivenLevel called with level: " << level << '\n';

/*	if (node.isRootNode)
		return;*/

	if (level == 1) {
		std::cout << node.literal << " ";
		if (node.type != Type::Literal){
			node.type = Type::Literal;
			if (performOperation(node) != -6969)
				node.literal = performOperation(node);
		}
	} else if (level > 1){
		for (ASTNode &child : node.children)
			printGivenLevel(child, level-1);
	}

}

int height(const ASTNode &node) {
/*	if (node.isRootNode)
		return 0;*/

	int maxHeight = 0;
	for (const ASTNode &child : node.children) {
		int h = height(child);
		if (h > maxHeight)
			maxHeight = h;
	}

	return maxHeight + 1;
}

void reverseLevelOrder(ASTNode &root) {
	int h = height(root);
	std::cout << "Got height of tree: " << h << '\n';
	int i;
	for (i = h; i >= 1; i--){
		printGivenLevel(root, i);
	}
}

double operationed(ASTNode &tree) {
	for (ASTNode &child : tree.children){

	}

	tree.type = Type::Literal;
	tree.literal = performOperation(tree);

	return performOperation(tree);
}

string result(const string &input) {
	// 1 + 2*3
	//
	// add
	// 1 mul
	//   2 3
	//
	
	/*ASTNode tree(Type::Operation, Operation::Add, CHILDREN{
		ASTNode(Type::Literal, 1),
		ASTNode(Type::Operation, Operation::Mul, CHILDREN{
			ASTNode(Type::Literal, 2), ASTNode(Type::Literal, 3)
		})
	});*/

	// 69 + 2 * (3 + 3)
	ASTNode tree(Type::Operation, Operation::Add, CHILDREN{
		ASTNode(Type::Literal, 69),
		ASTNode(Type::Operation, Operation::Mul, CHILDREN{
			ASTNode(Type::Literal, 2), ASTNode(Type::Operation, Operation::Add, CHILDREN{
					ASTNode(Type::Literal, 3), ASTNode(Type::Literal, 3)
			})
		})
	});

	tree.isRootNode = true;
	reverseLevelOrder(tree);
	std::cout << "Result: " << tree.literal << '\n';

	ASTNode x = ASTNode(Type::Operation, Operation::Mul, CHILDREN{
		ASTNode(Type::Literal, 2), ASTNode(Type::Literal, 3)
	});

//	std::cout << "operationed: " << performOperation(x) << '\n';

	return "";
}

int main() {
	std::cout << "Input: ";

	string input;
	std::getline(std::cin, input);

	std::cout << result(input) << '\n';
}
