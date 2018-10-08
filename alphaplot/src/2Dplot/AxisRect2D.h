/* This file is part of AlphaPlot.
   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   AlphaPlot is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   AlphaPlot is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with AlphaPlot.  If not, see <http://www.gnu.org/licenses/>.

   Description : axis rect related stuff */

#ifndef AXISRECT2D_H
#define AXISRECT2D_H

#include "../3rdparty/qcustomplot/qcustomplot.h"
#include "Axis2D.h"
#include "Bar2D.h"
#include "Curve2D.h"
#include "Grid2D.h"
#include "LineSpecial2D.h"
#include "Pie2D.h"
#include "Plot2D.h"
#include "Spline2D.h"
#include "StatBox2D.h"
#include "Vector2D.h"

class Legend2D;
class Table;
class Column;
class TextItem2D;
class StatBox2D;
class LineItem2D;

class AxisRect2D : public QCPAxisRect {
  Q_OBJECT
 private:
  typedef QPair<QPair<Grid2D *, Axis2D *>, QPair<Grid2D *, Axis2D *>> GridPair;
  typedef QVector<TextItem2D *> TextItemVec;
  typedef QVector<LineItem2D *> LineItemVec;
  typedef QVector<LineSpecial2D *> LsVec;
  typedef QVector<Curve2D *> CurveVec;
  typedef QVector<Spline2D *> SplineVec;
  typedef QVector<Vector2D *> VectorVec;
  typedef QVector<Bar2D *> BarVec;
  typedef QVector<StatBox2D *> StatBoxVec;
  typedef QVector<Pie2D *> PieVec;

 public:
  explicit AxisRect2D(Plot2D *parent, bool setupDefaultAxis = false);
  ~AxisRect2D();

  void setAxisRectBackground(const QBrush &brush);
  Axis2D *addAxis2D(const Axis2D::AxisOreantation &orientation);
  bool removeAxis2D(Axis2D *axis);
  QBrush getAxisRectBackground() const;
  Grid2D *bindGridTo(Axis2D *axis);

  QList<Axis2D *> getAxes2D() const;
  QList<Axis2D *> getAxes2D(const Axis2D::AxisOreantation &orientation) const;
  QList<Axis2D *> getXAxes2D() const;
  QList<Axis2D *> getYAxes2D() const;
  GridPair getGridPair() const { return gridpair_; }
  TextItemVec getTextItemVec() const { return textvec_; }
  LineItemVec getLineItemVec() const { return linevec_; }
  LsVec getLsVec() const { return lsvec_; }
  CurveVec getCurveVec() const { return curvevec_; }
  SplineVec getSplineVec() const { return splinevec_; }
  VectorVec getVectorVec() const { return vectorvec_; }
  BarVec getBarVec() const { return barvec_; }
  StatBoxVec getStatBoxVec() const { return statboxvec_; }
  PieVec getPieVec() const { return pievec_; }

  Axis2D *getXAxis(int value);
  Axis2D *getYAxis(int value);
  Plot2D *getParentPlot2D() { return plot2d_; }

  enum class LineScatterType {
    Line2D,
    Scatter2D,
    LineAndScatter2D,
    Area2D,
  };

  enum class LineScatterSpecialType {
    VerticalDropLine2D,
    CentralStepAndScatter2D,
    HorizontalStep2D,
    VerticalStep2D,
  };

  enum class BarType {
    HorizontalBars,
    VerticalBars,
  };

  LineSpecial2D *addLineScatter2DPlot(const LineScatterSpecialType &type,
                                      Table *table, Column *xData,
                                      Column *yData, int from, int to,
                                      Axis2D *xAxis, Axis2D *yAxis);
  Curve2D *addCurve2DPlot(const AxisRect2D::LineScatterType &type, Table *table,
                          Column *xcol, Column *ycol, int from, int to,
                          Axis2D *xAxis, Axis2D *yAxis);
  Spline2D *addSpline2DPlot(Table *table, Column *xData, Column *yData,
                            int from, int to, Axis2D *xAxis, Axis2D *yAxis);
  Curve2D *addFunction2DPlot(QVector<double> *xdata, QVector<double> *ydata,
                             Axis2D *xAxis, Axis2D *yAxis, const QString &name);
  Bar2D *addBox2DPlot(const BarType &type, Table *table, Column *xData,
                      Column *yData, int from, int to, Axis2D *xAxis,
                      Axis2D *yAxis);
  Vector2D *addVectorPlot(const Vector2D::VectorPlot &vectorplot, Table *table,
                          Column *x1Data, Column *y1Data, Column *x2Data,
                          Column *y2Data, int from, int to, Axis2D *xAxis,
                          Axis2D *yAxis);
  StatBox2D *addStatBox2DPlot(Table *table, StatBox2D::BoxWhiskerData data,
                              Axis2D *xAxis, Axis2D *yAxis);
  Pie2D *addPie2DPlot(Table *table, Column *xData, int from, int to);
  TextItem2D *addTextItem2D(QString text);
  LineItem2D *addLineItem2D();

  QList<Axis2D *> getAxesOrientedTo(
      const Axis2D::AxisOreantation &orientation) const;

  Legend2D *getLegend() const { return axisRectLegend_; }
  void updateLegendRect();
  void selectAxisRect();

  // select axisrect with mouse click
  void setSelected(const bool status);
  void drawSelection(QCPPainter *painter);
  bool isSelected() { return isAxisRectSelected_; }

  // remove
  bool removeTextItem2D(TextItem2D *textitem);
  bool removeLineItem2D(LineItem2D *lineitem);
  bool removeLineScatter2D(LineSpecial2D *ls);
  bool removeCurve2D(Curve2D *curve);
  bool removeSpline2D(Spline2D *spline);
  bool removeStatBox2D(StatBox2D *statbox);
  bool removeVector2D(Vector2D *vector);
  bool removeBar2D(Bar2D *bar);
  bool removePie2D(Pie2D *pie);

  void setPrintorExportJob(bool value) { printorexportjob_ = value; }

 public slots:
  Axis2D *addLeftAxis2D() { return addAxis2D(Axis2D::AxisOreantation::Left); }
  Axis2D *addBottomAxis2D() {
    return addAxis2D(Axis2D::AxisOreantation::Bottom);
  }
  Axis2D *addRightAxis2D() { return addAxis2D(Axis2D::AxisOreantation::Right); }
  Axis2D *addTopAxis2D() { return addAxis2D(Axis2D::AxisOreantation::Top); }

 protected:
  void mousePressEvent(QMouseEvent *, const QVariant &);
  void draw(QCPPainter *painter);

 signals:
  void AxisRectClicked(AxisRect2D *);
  // created
  void Axis2DCreated(Axis2D *);
  void TextItem2DCreated(TextItem2D *);
  void LineItem2DCreated(LineItem2D *);
  void LineScatter2DCreated(LineSpecial2D *);
  void Curve2DCreated(Curve2D *);
  void Spline2DCreated(Spline2D *);
  void StatBox2DCreated(StatBox2D *);
  void Vector2DCreated(Vector2D *);
  void Bar2DCreated(Bar2D *);
  void Pie2DCreated(Pie2D *);
  // Removed
  void Axis2DRemoved(AxisRect2D *);
  void TextItem2DRemoved(AxisRect2D *);
  void LineItem2DRemoved(AxisRect2D *);
  void LineScatter2DRemoved(AxisRect2D *);
  void Curve2DRemoved(AxisRect2D *);
  void Spline2DRemoved(AxisRect2D *);
  void StatBox2DRemoved(AxisRect2D *);
  void Vector2DRemoved(AxisRect2D *);
  void Bar2DRemoved(AxisRect2D *);
  void Pie2DRemoved(AxisRect2D *);

 private slots:
  void legendClick();
  void addfunctionplot();
  void exportGraph();
  void addplot();

 private:
  Plot2D *plot2d_;
  QBrush axisRectBackGround_;
  Legend2D *axisRectLegend_;
  bool isAxisRectSelected_;
  bool printorexportjob_;
  GridPair gridpair_;
  TextItemVec textvec_;
  LineItemVec linevec_;
  LsVec lsvec_;
  CurveVec curvevec_;
  SplineVec splinevec_;
  VectorVec vectorvec_;
  BarVec barvec_;
  StatBoxVec statboxvec_;
  PieVec pievec_;
  QList<Axis2D *> axes_;
  // QVector<QPair<StatBox2D *, QPair<Axis2D *, Axis2D *>>> statboxplots_;
  // Histogram
  // Other types
};

#endif  // AXISRECT2D_H
