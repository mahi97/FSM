#include "monitor.h"

Monitor* monitor;

Monitor::Monitor(QWidget *parent) : QGraphicsView(parent) {

    QGraphicsScene s;
    this->setScene(&s);
    //    m_scene = new QGVScene("DEMO");
//    this->setScene(m_scene);

//    connect(m_scene, SIGNAL(nodeContextMenu(QGVNode*)),
//           this    , SLOT(nodeContextMenu(QGVNode*)));
//    connect(m_scene, SIGNAL(nodeDoubleClick(QGVNode*)),
//            this   , SLOT(nodeDoubleClick(QGVNode*)));

}

Monitor::~Monitor() {

}

void Monitor::slt_show() {
    qDebug() << "gotcha !";


    /*
    m_scene->loadLayout("digraph test{node [style=filled,fillcolor=white];N1 -> N2;N2 -> N3;N3 -> N4;N4 -> N1;}");
    connect(m_scene, SIGNAL(nodeContextMenu(QGVNode*)), SLOT(nodeContextMenu(QGVNode*)));
    connect(m_scene, SIGNAL(nodeDoubleClick(QGVNode*)), SLOT(nodeDoubleClick(QGVNode*)));
    ui->graphicsView->setScene(m_scene);
    return;
    */

    //Configure scene attributes
    m_scene->setGraphAttribute("label", "DEMO");

    m_scene->setGraphAttribute("splines", "ortho");
    m_scene->setGraphAttribute("rankdir", "LR");
    //m_scene->setGraphAttribute("concentrate", "true"); //Error !
    m_scene->setGraphAttribute("nodesep", "0.4");

    m_scene->setNodeAttribute("shape", "box");
    m_scene->setNodeAttribute("style", "filled");
    m_scene->setNodeAttribute("fillcolor", "white");
    m_scene->setNodeAttribute("height", "1.2");
    m_scene->setEdgeAttribute("minlen", "3");
    //m_scene->setEdgeAttribute("dir", "both");

    //Add some nodes
    QGVNode *node1 = m_scene->addNode("BOX");
    node1->setIcon(QImage(":/icons/Gnome-System-Run-64.png"));
    QGVNode *node2 = m_scene->addNode("SERVER0");
    node2->setIcon(QImage(":/icons/Gnome-Network-Transmit-64.png"));
    QGVNode *node3 = m_scene->addNode("SERVER1");
    node3->setIcon(QImage(":/icons/Gnome-Network-Transmit-64.png"));
    QGVNode *node4 = m_scene->addNode("USER");
    node4->setIcon(QImage(":/icons/Gnome-Stock-Person-64.png"));
    QGVNode *node5 = m_scene->addNode("SWITCH");
    node5->setIcon(QImage(":/icons/Gnome-Network-Server-64.png"));

    //Add some edges
    m_scene->addEdge(node1, node2, "TTL")->setAttribute("color", "red");
    m_scene->addEdge(node1, node2, "SERIAL");
    m_scene->addEdge(node1, node3, "RAZ")->setAttribute("color", "blue");
    m_scene->addEdge(node2, node3, "SECU");

    m_scene->addEdge(node2, node4, "STATUS")->setAttribute("color", "red");

    m_scene->addEdge(node4, node3, "ACK")->setAttribute("color", "red");

    m_scene->addEdge(node4, node2, "TBIT");
    m_scene->addEdge(node4, node2, "ETH");
    m_scene->addEdge(node4, node2, "RS232");

    m_scene->addEdge(node4, node5, "ETH1");
    m_scene->addEdge(node2, node5, "ETH2");

    QGVSubGraph *sgraph = m_scene->addSubGraph("SUB1");
    sgraph->setAttribute("label", "OFFICE");

    QGVNode *snode1 = sgraph->addNode("PC0152");
    QGVNode *snode2 = sgraph->addNode("PC0153");

    m_scene->addEdge(snode1, snode2, "RT7");

    m_scene->addEdge(node3, snode1, "GB8");
    m_scene->addEdge(node3, snode2, "TS9");


    QGVSubGraph *ssgraph = sgraph->addSubGraph("SUB2");
    ssgraph->setAttribute("label", "DESK");
    m_scene->addEdge(snode1, ssgraph->addNode("PC0155"), "S10");

    //Layout scene
    m_scene->applyLayout();

    //Fit in view
    this->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);


}

void Monitor::nodeContextMenu(QGVNode *node) {
    //Context menu exemple
    QMenu menu(node->label());

    menu.addSeparator();
    menu.addAction(tr("Informations"));
    menu.addAction(tr("Options"));

    QAction *action = menu.exec(QCursor::pos());
    if(action == 0)
        return;
}

void Monitor::nodeDoubleClick(QGVNode *node) {
    QMessageBox::information(this, tr("Node double clicked"), tr("Node %1").arg(node->label()));

}

