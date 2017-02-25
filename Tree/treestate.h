#ifndef TREE_TREESTATE_H
#define TREE_TREESTATE_H

#include "treenode.h"
#include <QObject>

/*
 * A graph state stores the root element of an existential graph tree. It also
 * provides an interface to interact with the graph itself (such as selecting a
 * region and handling a modify command), which will handle any substantial
 * changes within the graph.
 *
 * The constructor makes a new root node and selects it.
 *
 * Change selection will update the selected graph element (which will serve as
 * the source of modifications, additions, and removals).
 *
 * Additions will try and add a child of a specific type to the selected
 * region. If the selected region is a statement (which is not allowed to have
 * children of its own), then the addition will add it as a child of the
 * selected region's parent (i.e. make it a new sibling to the selected
 * statement).
 *
 * Removals come in two flavors: saveOrphans will transfer all of the selected
 * region's children to their grandparent; burnTheOrphanage will remove and kill
 * all of the selected region's children if they have any. In either case, the
 * selected region will be removed from the tree. Root elements are not allowed
 * to be removed.
 *
 * Surround with cut simply adds a cut above the selected region in the tree.
 */
class TreeState : public QObject
{
    Q_OBJECT

public:
    TreeState(): root(new TreeNode()), selected(root){}
    TreeState(TreeState* original):
        root(new TreeNode(original->getCopiedRoot())), selected(root){}
    ~TreeState() {}

    /* Change selection */
    void selectAChild();
    void selectParent();
    void selectRoot();
    void selectLeftSibling();
    void selectRightSibling();

    /* TODO: multiple selection? */

    /* Add */
    void addChildCut();
    void addChildDoubleCut();
    void addChildStatement(QString s);

    /* Remove */
    void removeAndSaveOrphans();
    void removeAndBurnTheOrphanage();

    /* Copy */
    static TreeState* copyState(TreeState* currentTree);
    TreeNode* getCopiedRoot(){ return new TreeNode(this->root); }

    /* Surround with cut */
    void surroundWithCut();
    void surroundWithDoubleCut();

    /* Print */
    void printTree();

    /* TODO: inference mode*/

    /* boxed string */
    QString getBoxedString();

signals:
    void treeChanged(QString s);

private:
    TreeNode* root;
    TreeNode* selected; /* TODO: List<> for multi-select? */

    QString getFormattedString();
};

#endif // TREE_TREESTATE_H
