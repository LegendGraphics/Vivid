
#include "common/Node.h"
#include "common/NodeVisitor.h"
#include "common/SpaceState.h"

using namespace te;




int main(int argc, char** argv)
{ 

    Node* root = new Node;
    root->setName("root");
    root->addComponent<SpaceState>(Vector3(0.0f, 0.0f, 0.0f));


    Node* n1 = new Node;
    n1->setName("n1");
    n1->addComponent<SpaceState>(0.0f, 0.0f, 0.0f);

    Node* n2 = new Node;
    n2->setName("n2");
    n2->addComponent<SpaceState>(0.0f, 0.0f, 0.0f);

    Node* m1 = new Node;
    m1->setName("m1");
    m1->addComponent<SpaceState>(0.0f, 0.0f, 0.0f);

    Node* m2 = new Node;
    m2->setName("m2");
    m2->addComponent<SpaceState>(0.0f, 0.0f, 0.0f);

    root->addChild(n1);
    root->addChild(n2);
    n1->addChild(m1);
    n2->addChild(m2);

    root->accept(new NodeVisitor(NodeVisitor::TraversalMode::TRAVERSE_CHILDREN,
        NodeVisitor::VisitorType::NONE_UPDATE));

    delete root;

    getchar();
    return 0;
}

