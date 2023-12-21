/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: fmckenna

#include "WorkflowAppHydroUQ.h"
#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <HydroEventSelection.h>
#include <RunLocalWidget.h>
#include <QProcess>
#include <QCoreApplication>
#include <RemoteService.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QHostInfo>
#include <QUuid>
#include <QSvgWidget>


#include <SimCenterComponentSelection.h>
#include "GeneralInformationWidget.h"
#include <SIM_Selection.h>
#include <RandomVariablesContainer.h>
#include <FEA_Selection.h>
#include <QDir>
#include <QFile>
#include <UQ_EngineSelection.h>
#include <LocalApplication.h>
#include <RemoteApplication.h>
#include <RemoteJobManager.h>
#include <RunWidget.h>
#include <InputWidgetBIM.h>
#include <UQ_EngineSelection.h>
#include <UQ_Results.h>

#include <EDP_Selection.h>

#include "CustomizedItemModel.h"

#include <QSettings>
#include <QUuid>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QHostInfo>

#include <Utils/ProgramOutputDialog.h>
#include <Utils/RelativePathResolver.h>
#include <GoogleAnalytics.h>

// static pointer for global procedure set in constructor
static WorkflowAppHydroUQ *theApp = 0;

// global procedure
int getNumParallelTasks() {
    return theApp->getMaxNumParallelTasks();
}

WorkflowAppHydroUQ::WorkflowAppHydroUQ(RemoteService *theService, QWidget *parent)
    : WorkflowAppWidget(theService, parent)
{
    // set static pointer for global procedure
    theApp = this;

    //
    // create the various widgets
    //

    theRVs = RandomVariablesContainer::getInstance();
    theGI = GeneralInformationWidget::getInstance();
    theSIM = new SIM_Selection(true, true);
    theEventSelection = new HydroEventSelection(theRVs, theGI, this);
    theAnalysisSelection = new FEA_Selection(true);
    theUQ_Selection = new UQ_EngineSelection(ForwardReliabilitySensitivity);
    theEDP_Selection = new EDP_Selection(theRVs);

    //theResults = new DakotaResultsSampling(theRVs);
    theResults = theUQ_Selection->getResults();

    localApp = new LocalApplication("sWHALE.py");
    remoteApp = new RemoteApplication("sWHALE.py", theService);

    //    localApp = new LocalApplication("Hydro-UQ workflow.py");
    //   remoteApp = new RemoteApplication("Hydro-UQ workflow.py", theService);

    // localApp = new LocalApplication("Hydro-UQ.py");
    // remoteApp = new RemoteApplication("Hydro-UQ.py", theService);
    theJobManager = new RemoteJobManager(theService);

    SimCenterWidget *theWidgets[1];// =0;
    theRunWidget = new RunWidget(localApp, remoteApp, theWidgets, 0);

    //
    // connect signals and slots
    //

    // error messages and signals


    connect(localApp,SIGNAL(setupForRun(QString &,QString &)), this, SLOT(setUpForApplicationRun(QString &,QString &)));
    connect(this,SIGNAL(setUpForApplicationRunDone(QString&, QString &)), theRunWidget, SLOT(setupForRunApplicationDone(QString&, QString &)));
    connect(localApp,SIGNAL(processResults(QString&)), this, SLOT(processResults(QString&)));
    connect(theJobManager,SIGNAL(processResults(QString&)), this, SLOT(processResults(QString&)));
    connect(remoteApp,SIGNAL(setupForRun(QString &,QString &)), this, SLOT(setUpForApplicationRun(QString &,QString &)));
    connect(theJobManager,SIGNAL(loadFile(QString&)), this, SLOT(loadFile(QString&)));

    connect(remoteApp,SIGNAL(successfullJobStart()), theRunWidget, SLOT(hide()));
       
    //connect(theRunLocalWidget, SIGNAL(runButtonPressed(QString, QString)), this, SLOT(runLocal(QString, QString)));


    //
    // create layout to hold component selectio
    //


    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    this->setLayout(horizontalLayout);
    this->setContentsMargins(0,5,0,5);
    horizontalLayout->setMargin(0);
    horizontalLayout->setSpacing(0);

    QSvgWidget *theSvgUQ  = new QSvgWidget();
    QSvgWidget *theSvgGI  = new QSvgWidget();
    QSvgWidget *theSvgSIM = new QSvgWidget();
    QSvgWidget *theSvgEVT = new QSvgWidget();
    QSvgWidget *theSvgFEM = new QSvgWidget();
    QSvgWidget *theSvgEDP = new QSvgWidget();
    QSvgWidget *theSvgRV  = new QSvgWidget();
    QSvgWidget *theSvgRES = new QSvgWidget();
    theSvgUQ->load(QString(":/icons/question-dimensions-white.svg"));
    theSvgGI->load(QString(":/icons/building-white.svg"));
    theSvgSIM->load(QString(":/icons/shape-3-white.svg"));
    theSvgEVT->load(QString(":/icons/ripple-white.svg"));
    theSvgFEM->load(QString(":/icons/vector-triangle-white.svg"));
    theSvgEDP->load(QString(":/icons/chart-arrows-white.svg"));
    theSvgRV->load(QString(":/icons/dice-6-white.svg"));
    theSvgRES->load(QString(":/icons/flag-white.svg"));
    // Set size of SVG to match the size of the test in the side bar at theComponentSelection, e.g. "UQ"
    
    int iconSize = 36;
    theSvgUQ->setFixedSize(iconSize,iconSize);
    theSvgGI->setFixedSize(iconSize,iconSize);
    theSvgSIM->setFixedSize(iconSize,iconSize);
    theSvgEVT->setFixedSize(iconSize,iconSize);
    theSvgFEM->setFixedSize(iconSize,iconSize);
    theSvgEDP->setFixedSize(iconSize,iconSize);
    theSvgRV->setFixedSize(iconSize,iconSize);
    theSvgRES->setFixedSize(iconSize,iconSize);

    // Set background color of SVG to match the background color of the side bar
    // theSvgUQ->setStyleSheet("background-color: rgb(79, 83, 89)");
    // theSvgGI->setStyleSheet("background-color: rgb(79, 83, 89)");
    // theSvgSIM->setStyleSheet("background-color: rgb(79, 83, 89)");
    // theSvgEVT->setStyleSheet("background-color: rgb(79, 83, 89)");
    // theSvgFEM->setStyleSheet("background-color: rgb(79, 83, 89)");
    // theSvgEDP->setStyleSheet("background-color: rgb(79, 83, 89)");
    // theSvgRV->setStyleSheet("background-color: rgb(79, 83, 89)");
    // theSvgRES->setStyleSheet("background-color: rgb(79, 83, 89)");
    // Set the size policy of the SVG to be fixed
    theSvgUQ->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    theSvgGI->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    theSvgSIM->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    theSvgEVT->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    theSvgFEM->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    theSvgEDP->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    theSvgRV->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    theSvgRES->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Set the contents margins of the SVG to be 0
    theSvgUQ->setContentsMargins(0,10,0,10);
    theSvgGI->setContentsMargins(0,10,0,10);
    theSvgSIM->setContentsMargins(0,10,0,10);
    theSvgEVT->setContentsMargins(0,10,0,10);
    theSvgFEM->setContentsMargins(0,10,0,10);
    theSvgEDP->setContentsMargins(0,10,0,10);
    theSvgRV->setContentsMargins(0,10,0,10);
    theSvgRES->setContentsMargins(0,10,0,10);
    theSvgUQ->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");
    theSvgGI->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");
    theSvgSIM->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");
    theSvgEVT->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");
    theSvgFEM->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");
    theSvgEDP->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");
    theSvgRV->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");
    theSvgRES->setStyleSheet(":hover{background-color: rgb(69, 187, 217)}");

    // theSvgUQ->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");
    // theSvgGI->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");
    // theSvgSIM->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");
    // theSvgEVT->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");
    // theSvgFEM->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");
    // theSvgEDP->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");
    // theSvgRV->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");
    // theSvgRES->setStyleSheet(":selected:active{background-color:  rgb(63, 147, 168)}");


// :active{
//     background: rgb(63, 147, 168);
// }

// QTreeView#treeViewOnTheLeft::item:selected:!active {
//     background: rgb(63, 147, 168);
// }
    // Now, place the SVG in a frame



    // QDir dir("/home/");
    // QString s;
    // s = dir.relativeFilePath("images/file.jpg");     // s is "images/file.jpg"


    QVBoxLayout *verticalIconLayout = new QVBoxLayout();
    verticalIconLayout->addWidget(theSvgUQ);
    verticalIconLayout->addWidget(theSvgGI);
    verticalIconLayout->addWidget(theSvgSIM);
    verticalIconLayout->addWidget(theSvgEVT);
    verticalIconLayout->addWidget(theSvgFEM);
    verticalIconLayout->addWidget(theSvgEDP);
    verticalIconLayout->addWidget(theSvgRV);
    verticalIconLayout->addWidget(theSvgRES);
    verticalIconLayout->setAlignment(Qt::AlignTop);
    verticalIconLayout->setSpacing(13.5);
    verticalIconLayout->setContentsMargins(0,5,0,5);

    sideBarIconFrame = new QFrame();
    sideBarIconFrame->setLayout(verticalIconLayout);
    // sideBarIconFrame->setStyleSheet(":hover{background-color: rgb(79, 83, 89)}");
    sideBarIconFrame->setStyleSheet("background-color: rgb(79, 83, 89)");
    sideBarIconFrame->setFrameShape(QFrame::NoFrame);
    sideBarIconFrame->setLineWidth(0);
    sideBarIconFrame->setContentsMargins(0,10,0,10);
    // sideBarIconFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // sideBarIconFrame->setFixedWidth(25);
    // sideBarIconFrame->setFixedHeight(800);


    // Now, place the frame in the side bar
    horizontalLayout->addWidget(sideBarIconFrame);



    //
    // create the component selection & add the components to it
    //

    theComponentSelection = new SimCenterComponentSelection();
    horizontalLayout->addWidget(theComponentSelection);

    theComponentSelection->addComponent(QString("UQ"),  theUQ_Selection);
    theComponentSelection->addComponent(QString("GI"),  theGI);
    theComponentSelection->addComponent(QString("SIM"), theSIM);
    theComponentSelection->addComponent(QString("EVT"), theEventSelection);
    theComponentSelection->addComponent(QString("FEM"), theAnalysisSelection);
    theComponentSelection->addComponent(QString("EDP"), theEDP_Selection);
    theComponentSelection->addComponent(QString("RV"),  theRVs);
    theComponentSelection->addComponent(QString("RES"), theResults);
    theComponentSelection->displayComponent("EVT"); // Initial page on startup


    horizontalLayout->setAlignment(Qt::AlignLeft);
    // create the side bar icons in QT
    // Need to place SVG in a frame to get it to display properly
    // The frame is then placed in the side bar
    // QSvgWidget *theSvg = new QSvgWidget();
    // theSvg->load(QString("./icons/engine-white.svg"));
    // theSvg->setFixedSize(50,50);
    // theSvg->setStyleSheet("background-color: rgb(0,0,0,0)");
    // theSvg->setContentsMargins(0,0,0,0);
    // theSvg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // // Now, place the SVG in a frame
    // QFrame *frame = new QFrame();
    // frame->setFixedSize(50,50);
    // frame->setStyleSheet("background-color: rgb(0,0,0,0)");
    // frame->setContentsMargins(0,0,0,0);
    // frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // QVBoxLayout *verticalLayout = new QVBoxLayout();
    // verticalLayout->setContentsMargins(0,0,0,0);
    // verticalLayout->addWidget(theSvg);
    // frame->setLayout(verticalLayout);

    // // Now, place the frame in the side bar
    // horizontalLayout->addWidget(frame);

    // // Now, repeat for each icon
    // theSvg = new QSvgWidget();
    // theSvg->load(QString("./icons/building-white.svg"));
    // theSvg->setFixedSize(50,50);
    // theSvg->setStyleSheet("background-color: rgb(0,0,0,0)");
    // theSvg->setContentsMargins(0,0,0,0);
    // theSvg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // frame = new QFrame();
    // frame->setFixedSize(50,50);
    // frame->setStyleSheet("background-color: rgb(0,0,0,0)");
    // frame->setContentsMargins(0,0,0,0);
    // frame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // verticalLayout = new QVBoxLayout();
    // verticalLayout->setContentsMargins(0,0,0,0);
    // verticalLayout->addWidget(theSvg);
    // frame->setLayout(verticalLayout);
    // horizontalLayout->addWidget(frame);

    // access a web page which will increment the usage count for this tool
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://opensees.berkeley.edu/OpenSees/developer/eeuq/use.php")));


    //
    // set the defults in the General Info
    //

    theGI->setDefaultProperties(1,144,360,360,37.8715,-122.2730);
}

WorkflowAppHydroUQ::~WorkflowAppHydroUQ()
{
    // hack to get around a sometimes occuring seg fault
    // as some classes in destructur remove RV from the RVCOntainer
    // which may already have been destructed .. so removing so no destructor called

  //    QWidget *newUQ = new QWidget();
  //    theComponentSelection->swapComponent("RV",newUQ);
}

void WorkflowAppHydroUQ::replyFinished(QNetworkReply *pReply)
{
    return;
}


bool
WorkflowAppHydroUQ::outputToJSON(QJsonObject &jsonObjectTop) {

    //
    // get each of the main widgets to output themselves
    //
  
    bool result = true;
    QJsonObject apps;

    //
    // get each of the main widgets to output themselves to top 
    // and workflow widgets to outut appData to apps
    //

    // theGI
    QJsonObject jsonObjGenInfo;
    result = theGI->outputToJSON(jsonObjGenInfo);
    if (result == false)
        return result;
    jsonObjectTop["GeneralInformation"] = jsonObjGenInfo;

    // theRVs
    result = theRVs->outputToJSON(jsonObjectTop);
    if (result == false)
        return result;

    // theEDP
    QJsonObject jsonObjectEDP;
    result = theEDP_Selection->outputToJSON(jsonObjectEDP);
    if (result == false)
        return result;
    jsonObjectTop["EDP"] = jsonObjectEDP;

    QJsonObject appsEDP;
    result = theEDP_Selection->outputAppDataToJSON(appsEDP);
    if (result == false)
        return result;
    apps["EDP"]=appsEDP;

    // theUQ
    result = theUQ_Selection->outputAppDataToJSON(apps);
    if (result == false)
        return result;
    
    result = theUQ_Selection->outputToJSON(jsonObjectTop);
    if (result == false)
        return result;

    // theSIM
    result = theSIM->outputAppDataToJSON(apps);
    if (result == false)
        return result;

    result = theSIM->outputToJSON(jsonObjectTop);
    if (result == false)
        return result;

    // theAnalysis
    result = theAnalysisSelection->outputAppDataToJSON(apps);
    if (result == false)
        return result;

    result = theAnalysisSelection->outputToJSON(jsonObjectTop);
    if (result == false)
        return result;

    // theEventSelection
    // NOTE: Events treated differently, due to array nature of objects
    result = theEventSelection->outputToJSON(jsonObjectTop);
    if (result == false)
        return result;

    result = theEventSelection->outputAppDataToJSON(apps);
    if (result == false)
        return result;

    result = theRunWidget->outputToJSON(jsonObjectTop);
    if (result == false)
        return result;

    // theResults
    // sy - to save results
    result = theResults->outputToJSON(jsonObjectTop);
    if (result == false)
        return result;

    jsonObjectTop["Applications"]=apps;

    QJsonObject defaultValues;
    defaultValues["workflowInput"]=QString("scInput.json");    
    defaultValues["filenameAIM"]=QString("AIM.json");
    defaultValues["filenameEVENT"] = QString("EVENT.json");
    defaultValues["filenameSAM"]= QString("SAM.json");
    defaultValues["filenameEDP"]= QString("EDP.json");
    defaultValues["filenameSIM"]= QString("SIM.json");
    defaultValues["driverFile"]= QString("driver");
    defaultValues["filenameDL"]= QString("BIM.json");
    defaultValues["workflowOutput"]= QString("EDP.json");
    QJsonArray rvFiles, edpFiles;
    rvFiles.append(QString("AIM.json"));
    rvFiles.append(QString("SAM.json"));
    rvFiles.append(QString("EVENT.json"));
    rvFiles.append(QString("SIM.json"));
    edpFiles.append(QString("EDP.json"));
    defaultValues["rvFiles"]= rvFiles;
    defaultValues["edpFiles"]=edpFiles;
    jsonObjectTop["DefaultValues"]=defaultValues;

    return result;
}


void WorkflowAppHydroUQ::processResults(QString &dirName)
{


  //
  // get results widget for currently selected UQ option
  //

  theResults=theUQ_Selection->getResults();
  if (theResults == NULL) {
    this->errorMessage("FATAL - UQ option selected not returning results widget");
    return;
  }

  //
  // connect signals for results widget
  //

  /*
  connect(theResults,SIGNAL(sendStatusMessage(QString)), this,SLOT(statusMessage(QString)));
  connect(theResults,SIGNAL(sendErrorMessage(QString)), this,SLOT(errorMessage(QString)));
  */
  
  //
  // swap current results with existing one in selection & disconnect signals
  //

  QWidget *oldResults = theComponentSelection->swapComponent(QString("RES"), theResults);
  if (oldResults != NULL) {
    //disconnect(oldResults,SIGNAL(sendErrorMessage(QString)), this,SLOT(errorMessage(QString)));
    //disconnect(oldResults,SIGNAL(sendFatalMessage(QString)), this,SLOT(fatalMessage(QString)));  
    delete oldResults;
  }

  //
  // proess results
  // 

  theResults->processResults(dirName);
  theRunWidget->hide();
  theComponentSelection->displayComponent("RES");
}

void
WorkflowAppHydroUQ::clear(void)
{
    theGI->clear();
    theSIM->clear();
}

bool
WorkflowAppHydroUQ::inputFromJSON(QJsonObject &jsonObject)
{
    //
    // get each of the main widgets to input themselves
    //

    if (jsonObject.contains("GeneralInformation")) {
        QJsonObject jsonObjGeneralInformation = jsonObject["GeneralInformation"].toObject();
        if (theGI->inputFromJSON(jsonObjGeneralInformation) == false) {
            this->errorMessage("_UQ: failed to read GeneralInformation");
        }
    } else {
        this->errorMessage("Hydro_UQ: failed to find GeneralInformation");
        return false;
    }

    if (jsonObject.contains("Applications")) {

        QJsonObject theApplicationObject = jsonObject["Applications"].toObject();

        // note: Events is different because the object is an Array
        if (theApplicationObject.contains("Events")) {
            //  QJsonObject theObject = theApplicationObject["Events"].toObject(); it is null object, actually an array
            if (theEventSelection->inputAppDataFromJSON(theApplicationObject) == false) {
                this->errorMessage("Hydro_UQ: failed to read Event Application");
            }

        } else {
            this->errorMessage("Hydro_UQ: failed to find Event Application");
            return false;
        }

        if (theUQ_Selection->inputAppDataFromJSON(theApplicationObject) == false)
            this->errorMessage("Hydro_UQ: failed to read UQ application");

        if (theSIM->inputAppDataFromJSON(theApplicationObject) == false)
            this->errorMessage("Hydro_UQ: failed to read SIM application");
    
        if (theAnalysisSelection->inputAppDataFromJSON(theApplicationObject) == false)
            this->errorMessage("Hydro_UQ: failed to read FEM application");

        if (theApplicationObject.contains("EDP")) {
            QJsonObject theObject = theApplicationObject["EDP"].toObject();
            if (theEDP_Selection->inputAppDataFromJSON(theObject) == false) {
                this->errorMessage("Hydro_UQ: failed to read EDP application");
            }
        } else {
            this->errorMessage("Hydro_UQ: failed to find EDP application");
            return false;
        }

    } else
        return false;

    /*
    ** Note to me - RVs and Events treated differently as both use arrays .. rethink API!
    */

    theEventSelection->inputFromJSON(jsonObject);
    theRVs->inputFromJSON(jsonObject);
    theRunWidget->inputFromJSON(jsonObject);

    if (jsonObject.contains("EDP")) {
        QJsonObject edpObj = jsonObject["EDP"].toObject();
        if (theEDP_Selection->inputFromJSON(edpObj) == false)
            this->errorMessage("Hydro_UQ: failed to read EDP data");
    } else {
        this->errorMessage("Hydro_UQ: failed to find EDP data");
        return false;
    }


    if (theUQ_Selection->inputFromJSON(jsonObject) == false)
       this->errorMessage("Hydro_UQ: failed to read UQ Method data");

    if (theAnalysisSelection->inputFromJSON(jsonObject) == false)
        this->errorMessage("Hydro_UQ: failed to read FEM Method data");

    if (theSIM->inputFromJSON(jsonObject) == false)
        this->errorMessage("Hydro_UQ: failed to read SIM Method data");

    // sy - to display results
    auto* theNewResults = theUQ_Selection->getResults();

    if (theNewResults->inputFromJSON(jsonObject) == false)
        this->errorMessage("Hydro_UQ: failed to read RES Method data");
    theResults->setResultWidget(theNewResults);

    this->statusMessage("Done Loading File");
    
    return true;  
}


void
WorkflowAppHydroUQ::onRunButtonClicked() {
    emit errorMessage("The HydroUQ application cannot be run locally. Please run remotely on DesignSafe.");
//    theRunWidget->hide();
//    theRunWidget->setMinimumWidth(this->width()*0.5);
//    theRunWidget->showLocalApplication();
//    GoogleAnalytics::ReportLocalRun();
}

void
WorkflowAppHydroUQ::onRemoteRunButtonClicked(){
    emit errorMessage("");

    bool loggedIn = theRemoteService->isLoggedIn();

    if (loggedIn == true) {
        theRunWidget->hide();
        theRunWidget->setMinimumWidth(this->width()*0.5);
        theRunWidget->showRemoteApplication();

    } else {
        errorMessage("ERROR - You Need to Login to DesignSafe to Run HydroUQ On TACC Super-Computers.");
    }

    GoogleAnalytics::ReportDesignSafeRun();
}

void
WorkflowAppHydroUQ::onRemoteGetButtonClicked(){

    emit errorMessage("");

    bool loggedIn = theRemoteService->isLoggedIn();

    if (loggedIn == true) {

        theJobManager->hide();
        theJobManager->updateJobTable("");
        theJobManager->show();

    } else {
        errorMessage("ERROR - You Need to Login to DesignSafe to Get HydroUQ Results From TACC Super-Computers.");
    }
}

void
WorkflowAppHydroUQ::onExitButtonClicked(){

}

void
WorkflowAppHydroUQ::setUpForApplicationRun(QString &workingDir, QString &subDir) {

    errorMessage("");

    //
    // create temporary directory in working dir
    // and copy all files needed to this directory by invoking copyFiles() on app widgets
    //

    // designsafe will need a unique name
    /* *********************************************
    will let ParallelApplication rename dir
    QUuid uniqueName = QUuid::createUuid();
    QString strUnique = uniqueName.toString();
    strUnique = strUnique.mid(1,36);
    QString tmpDirName = QString("tmp.SimCenter") + strUnique;
    *********************************************** */

    QString tmpDirName = QString("tmp.SimCenter");
    qDebug() << "TMP_DIR: " << tmpDirName;
    QDir workDir(workingDir);

    QString tmpDirectory = workDir.absoluteFilePath(tmpDirName);
    QDir destinationDirectory(tmpDirectory);

    if(destinationDirectory.exists()) {
      destinationDirectory.removeRecursively();
    } else
      destinationDirectory.mkpath(tmpDirectory);

    QString templateDirectory  = destinationDirectory.absoluteFilePath(subDir);
    destinationDirectory.mkpath(templateDirectory);

    // copyPath(path, tmpDirectory, false);
    theSIM->copyFiles(templateDirectory);
    theEventSelection->copyFiles(templateDirectory);
    theAnalysisSelection->copyFiles(templateDirectory);
    theUQ_Selection->copyFiles(templateDirectory);
    theEDP_Selection->copyFiles(templateDirectory);

    //
    // in new templatedir dir save the UI data into dakota.json file (same result as using saveAs)
    // NOTE: we append object workingDir to this which points to template dir
    //

    QString inputFile = templateDirectory + QDir::separator() + tr("scInput.json");

    QFile file(inputFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        //errorMessage();
        return;
    }
    QJsonObject json;
    if (this->outputToJSON(json) == false)
        return;

    json["runDir"]=tmpDirectory;
    json["WorkflowType"]="Building Simulation";


    QJsonDocument doc(json);
    file.write(doc.toJson());
    file.close();


    statusMessage("Set-Up Done .. Now Starting HydroUQ Application");
    emit setUpForApplicationRunDone(tmpDirectory, inputFile);
}

int
WorkflowAppHydroUQ::loadFile(QString &fileName){

    //
    // open file
    //

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        emit errorMessage(QString("Could Not Open File: ") + fileName);
        return -1; 
    }

    //
    // place contents of file into json object
    //

    QString val;
    val=file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObj = doc.object();

    // close file
    file.close();

    //Resolve absolute paths from relative ones
    QFileInfo fileInfo(fileName);
    SCUtils::ResolveAbsolutePaths(jsonObj, fileInfo.dir());
    
    //
    // clear current and input from new JSON
    //

    this->clear();
    bool result = this->inputFromJSON(jsonObj);
    
    if (result == false)
      return -1;
    else
      return 0;
}

int
WorkflowAppHydroUQ::getMaxNumParallelTasks() {
    return theUQ_Selection->getNumParallelTasks();
}
