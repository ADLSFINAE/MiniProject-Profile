#include "boardElems/board.h"

Board::Board(QGraphicsScene *scene ,QGraphicsRectItem *parent)
    :QGraphicsRectItem(parent)
{
    // initialization of my array, it's not seems like in pure c++, but it's QVector
    // and i used resize method for it
    this->initVectorOfBlocks();
    this->inizialization(scene);
    game = new Game();
    this->figuresPlacing(scene, true);
    this->figuresPlacing(scene, false);
    pointer_to_scene = scene;

    for(auto& elem : figures){
        QObject::connect(elem, &Figure::vahue, this, &Board::remove_from_scene);
        Pawn* pawn = dynamic_cast<Pawn*>(elem);
        if(pawn != nullptr){
            QObject::connect(pawn, &Pawn::createChangePawnWidget, this, &Board::createChangePawnWidget);
            QObject::connect(game, &Game::getPawnCollection, pawn, &Pawn::slotPawnCollection);
            QObject::connect(pawn, &Pawn::updateFiguresPositionsFromPawn, this, &Board::updateFiguresVec);
        }
        else{
            QObject::connect(elem, &Figure::updateFiguresPositions, this, &Board::updateFiguresVec);
        }

        King* king = dynamic_cast<King*>(elem);
        if(king != nullptr && !king->getColor()){
            QObject::connect(game, &Game::exportCEELOToKing, king, &King::getCEELO);
        }
    }

    QObject::connect(this, &Board::initGameVecs, game, &Game::editVecs);

}

QRectF Board::boundingRect() const
{
    return boardSizeRect;
}

QVector<QVector<Block *> > Board::getBoard()
{
    return arrOfBlocks;
}

void Board::updateFiguresVec(Figure *fig)
{
    for(auto& elem : figures){
        if(elem == fig){
            elem->setPosition(fig->getPosition().x(), fig->getPosition().y());
            emit initGameVecs(figures);
            break;
        }
    }
}

void Board::remove_from_scene(Figure *figure)
{
    pointer_to_scene->removeItem(figure);
    int iter = 0;
    for(auto& elem: figures){//ЗАПОЛНЕНИЕ ОСНОВНОГО
        if(elem == figure){
            figures.erase(figures.begin() + iter);
            emit initGameVecs(figures);
            break;
        }
        iter++;
    }
}

void Board::createChangePawnWidget(bool color, int posX, int posY)
{
    changePawnWidget = new ChangePawnWidget(color);
    changePawnWidget->show();
    if(color)
        for(auto& label : changePawnWidget->getFiguresVec(true)){
            QObject::connect(label, &FigureLabel::createSelectedFigure, this, &Board::createNewFigure);
    }
    else{
        for(auto& label : changePawnWidget->getFiguresVec(false))
            QObject::connect(label, &FigureLabel::createSelectedFigure, this, &Board::createNewFigure);
    }
    NEWFIGX = posX;
    NEWFIGY = posY;
}

void Board::createNewFigure(Figure* element)
{
    pointer_to_scene->addItem(element);
    element->setBoard(arrOfBlocks);
    element->setPosition(NEWFIGX, NEWFIGY);
    figures.push_back(element);
    emit initGameVecs(figures);
    changePawnWidget->hide();
    delete changePawnWidget;
}

void Board::figuresPlacing(QGraphicsScene* scene, bool isWhite)
{
    int cols, pawnCols;
    isWhite ? ({cols = 7; pawnCols = 6;}) : ({cols = 0; pawnCols = 1;});

    QVector<Figure* >figures_50 = {//ЗАПОЛНЕНИЕ ВРЕМЕННОГО
        new King(4, cols, isWhite),
        new Queen(3, cols, isWhite),
        new Horse(1, cols, isWhite),
        new Horse(6, cols, isWhite),
        new Elephant(2, cols, isWhite),
        new Elephant(5, cols, isWhite),
        new Rook(0, cols, isWhite),
        new Rook(7, cols, isWhite),
    };

    for(int rows = 0; rows < LongByX; rows++)
        figures_50.push_back(new Pawn(rows, pawnCols, isWhite));

    for (const auto& figure : figures_50) {
        scene->addItem(figure);
        game->initOfVecs(figure, isWhite);
        figure->setBoard(arrOfBlocks);
    }

    for(auto& elem: figures_50){//ЗАПОЛНЕНИЕ ОСНОВНОГО
        figures.push_back(elem);
    }
}

void Board::inizialization(QGraphicsScene *scene)
{
    scene->addItem(this);
    /*
    * Lets talk about how it gonna working: *
    * 1) we adding Board like a ITEM to scene; *
    * 2) in buildingBlock() function we set what our blocks have parent and it our BOARD; *
    * 3) cause we addItem() -> board, all items what have parent board adding with him like they are blocks; *
    */
    for(int i = 0; i < LongByX; i++){
        for(int j = 0; j < LongByY; j++){
            if(neededColorChecker(i, j))
                buildingBlock(Qt::gray, i, j);
            else
                buildingBlock(Qt::black, i, j);
        }
    }

}

void Board::buildingBlock(QBrush brush, int rows, int cols)
{
    arrOfBlocks[rows][cols] = new Block();
    arrOfBlocks[rows][cols]->setParentItem(this);

    arrOfBlocks[rows][cols]->setBlockPos(rows, cols);
    arrOfBlocks[rows][cols]->setRect(0, 0, GlobX, GlobY);
    arrOfBlocks[rows][cols]->setPos(rows * GlobX, cols * GlobY);
    arrOfBlocks[rows][cols]->setDefPen();
    arrOfBlocks[rows][cols]->changeColor(brush);
}

void Board::initVectorOfBlocks()
{
    arrOfBlocks.resize(LongByX);

    for (int i = 0; i < LongByY; i++) {
        arrOfBlocks[i].resize(LongByY);
    }
}


bool Board::neededColorChecker(int rows, int cols) const
{
    if((rows + cols) % 2 == 0)
        return true;
    else
        return false;
}



