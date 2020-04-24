#ifndef SCATTER3D_H
#define SCATTER3D_H


#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QItemModelScatterDataProxy>
#include <memory>

#include "3Dplot/Graph3DCommon.h"

class Custom3DInteractions;
class Matrix;
using namespace QtDataVisualization;

class Scatter3D : public QObject {
  Q_OBJECT
 public:
  Scatter3D(Q3DScatter *scatter);
  ~Scatter3D();

  void setmatrixdatamodel(Matrix *matrix);
  void setGradient();
  Matrix *getMatrix();

 private:
  Q3DScatter *graph_;
  Matrix *matrix_;
  Custom3DInteractions *custominter_;
  std::unique_ptr<QScatterDataArray> dataArray_;
  std::unique_ptr<QScatterDataProxy> dataProxy_;
  std::unique_ptr<QScatter3DSeries> dataSeries_;
  std::unique_ptr<QItemModelScatterDataProxy> modelDataProxy_;
};
#endif // SCATTER3D_H