/*
    This file is part of ciberRatoToolsSrc.

    Copyright (C) 2001-2011 Universidade de Aveiro

    ciberRatoToolsSrc is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ciberRatoToolsSrc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/**
 * @author Miguel Rodrigues
 */

#ifndef CBPARAMDIALOG_H
#define CBPARAMDIALOG_H
#include "ui_cbparamdialogbase.h"

#include "cbsimulator.h"
#include "cbparameters.h"

/*!
    \class cbParamDialog
    \brief Matching class for Configuring Parameters Dialog Form
*/
class cbParamDialog : public QDialog, private Ui::cbParamDialogBase
{
    Q_OBJECT

public:
    cbParamDialog( cbSimulator *sim, QWidget* parent = 0, Qt::WFlags fl = 0 );
    ~cbParamDialog();

protected:
    cbSimulator *simulator;
    cbParameters *currentParam;
    cbParameters *defaultParam;
    void setParamWidgets(cbParameters *);

protected slots:
    virtual void accept(void);
    void restoreDefaults(void);

};

#endif // CBPARAMDIALOG_H
