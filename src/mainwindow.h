#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QSlider>
#include <QButtonGroup>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLabel>

#include "ui/qdslider.h"
#include "ui/teleportwidget.h"
#include "ui/mapview_settings.h"
#include "ui/texturepicker.h"
#include "ui/modelpicker.h"
#include "ui/startup.h"
#include "ui/waterwidget.h"

#include "world.h"
#include "mapview.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    
private:
    QString getActionName(QObject* object) const;

    Ui::MainWindow* ui;

    QString DisplayMode;
    QString ToolBarItem;

    TeleportWidget*   teleportW;
    MapView_Settings* settingsW;
    TexturePicker*    texturepW;
    ModelPicker*      modelpickerW;

    void addDockWindow(const QString& title, QWidget* widget, Qt::DockWidgetArea area = Qt::RightDockWidgetArea);

    template<class T>
    void deleteObject(T object)
    {
        if(object != NULL)
            delete object;
    }

    Qt::WindowStates nonFullScreenState;

    // Editing mode = 1
    QDSlider* t_outer_radius;
    QDSlider* t_inner_radius;
    QDSlider* t_speed;
    QDSlider* t_rotationx;
    QDSlider* t_rotationy;
    QDSlider* t_rotationz;
    QDSlider* t_impend;
    QDSlider* t_scale;

    QButtonGroup* t_brush;

    QPushButton* t_brush_circle;
    QPushButton* t_brush_square;
    QPushButton* t_reset_transform;

    QComboBox* t_terrain_mode;
    QComboBox* t_brush_type;

    QCheckBox* t_terrain_maxHeight;

    QDoubleSpinBox* t_terrain_maximum_height;

    QLabel* t_terrain_mode_label;

    QLabel* t_brush_label;
    QLabel* t_brush_type_label;

    QLabel* t_outer_radius_label;
    QLabel* t_outer_radius_value_label;
    QLabel* t_inner_radius_label;
    QLabel* t_inner_radius_value_label;
    QLabel* t_speed_label;
    QLabel* t_speed_value_label;
    QLabel* t_rotationx_label;
    QLabel* t_rotationx_value_label;
    QLabel* t_rotationy_label;
    QLabel* t_rotationy_value_label;
    QLabel* t_rotationz_label;
    QLabel* t_rotationz_value_label;
    QLabel* t_impend_label;
    QLabel* t_impend_value_label;
    QLabel* t_scale_label;
    QLabel* t_scale_value_label;

    QList<QPair<QString, QVariant>> t_terrain_mode_0;
    QList<QPair<QString, QVariant>> t_terrain_mode_1;

    // Editing mode = 2
    QDSlider* t_flow;

    QLabel* t_flow_label;
    QLabel* t_flow_value_label;

    // Editing mode = 3
    QColorDialog* colorW;

    // Editing mode = 4
    WaterWidget* waterW;

    //
    QList<QString> mode0Actions;
    QList<QString> mode1Actions;
    QList<QString> mode2Actions;
    QList<QString> mode3Actions;
    QList<QString> mode4Actions;
<<<<<<< HEAD:src/mainwindow.h
=======
    QList<QString> mode5Actions;
>>>>>>> origin/netix:src/mainwindow.h

    void initMode();
    void showMode(QList<QString>& parentList);

    void addToolbarAction(QWidget* widget, QList<QString>& parentList);
    void hideToolbarActions();

    //
    StartUp* startUp;

    World*   world;
    MapView* mapView;

    bool** mapCoords;

signals:
    void setSpeedMultiplier(float multiplier);
    void setDisplayMode(int mode);
    void setModeEditing(int option);
    void setTerrainMode(int mode);

private slots:
    void setSpeedMultiplier();
    void setDisplayMode();
    void setToolBarItem();
    void setFullscreen(bool checked);

    void setTerrainMaximumHeightState(int state);

    void setBrushOuterRadius(double value);
    void setBrushInnerRadius(double value);
    void setBrushInnerRadiusMaximumValue(double maximum);
<<<<<<< HEAD:src/mainwindow.h
=======
    void resetModelBrush();
>>>>>>> origin/netix:src/mainwindow.h

    void setTerrain_Mode(int index);

    void setProjectData(ProjectFileData& data);

    void showTeleport();
    void showSettings();
    void showTexturePicker();
    void showAbout();
    void showProjectSettings();

    void openWorld(ProjectFileData projectData);
    void postInitializeSubWorldWidgets();

    void createMemoryProject(NewProjectData projectData);

    void loadNewProjectMapTilesIntoMemory();

    void takeScreenshot();
    void takeScreenshotAndUpload();

    void screenshotUploadDone(const QString& link);
    void screenshotUploadError(const QString& error);
};

#endif // MAINWINDOW_H