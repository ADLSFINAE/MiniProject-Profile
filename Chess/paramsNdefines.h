#ifndef PARAMSNDEFINES_H
#define PARAMSNDEFINES_H
#include <QString>
#include <QRectF>
#include <QSize>

namespace GlobVal{
const static int GlobX = 80;
const static int GlobY = 80;

const static int LongByX = 8;
const static int LongByY = 8;

const static int FigureCenterX = GlobX / 2;
const static int FigureCenterY = GlobY / 2;

const static int SceneLongX = GlobX * LongByX;
const static int SceneLongY = GlobY * LongByY;

const static int ViewLongX = SceneLongX + LongByX;
const static int ViewLongY = SceneLongY + LongByY;

const static QRectF blockSizeRect(0, 0, GlobX, GlobY);
const static QRectF figureSizeRect(0, 0, GlobX, GlobY);
const static QSize viewSizeSquare(ViewLongX, ViewLongY);
const static QRectF sceneSizeRect(0, 0, SceneLongX, SceneLongY);
const static QRectF boardSizeRect(0, 0, SceneLongX, SceneLongY);

//black figures .png defs and way
const QString pngBlackKing = ":/blackFigures/chesscom/blackFigures/bK.png";
const QString pngBlackQueen = ":/blackFigures/chesscom/blackFigures/bP.png";
const QString pngBlackRook = ":/blackFigures/chesscom/blackFigures/bR.png";
const QString pngBlackHorse = ":/blackFigures/chesscom/blackFigures/bN.png";
const QString pngBlackElephant = ":/blackFigures/chesscom/blackFigures/bB.png";
const QString pngBlackPawn = ":/blackFigures/chesscom/blackFigures/bP.png";

//white figures .png defs and way
const QString pngWhiteKing = ":/whiteFigures/chesscom/whiteFigures/wK.png";
const QString pngWhiteQueen = ":/whiteFigures/chesscom/whiteFigures/wQ.png";
const QString pngWhiteRook = ":/whiteFigures/chesscom/whiteFigures/wR.png";
const QString pngWhiteHorse = ":/whiteFigures/chesscom/whiteFigures/wN.png";
const QString pngWhiteElephant = ":/whiteFigures/chesscom/whiteFigures/wB.png";
const QString pngWhitePawn = ":/whiteFigures/chesscom/whiteFigures/wP.png";
};

#endif // PARAMSNDEFINES_H
