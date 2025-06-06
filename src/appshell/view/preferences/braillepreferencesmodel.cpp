/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-Studio-CLA-applies
 *
 * MuseScore Studio
 * Music Composition & Notation
 *
 * Copyright (C) 2023 MuseScore Limited
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "braillepreferencesmodel.h"

#include <QVariant>

#include "translation.h"

using namespace mu::appshell;
using namespace mu::braille;

BraillePreferencesModel::BraillePreferencesModel(QObject* parent)
    : QObject(parent), muse::Injectable(muse::iocCtxForQmlObject(this))
{
}

void BraillePreferencesModel::load()
{
    brailleConfiguration()->braillePanelEnabledChanged().onNotify(this, [this]() {
        emit braillePanelEnabledChanged(braillePanelEnabled());
    });

    brailleConfiguration()->intervalDirectionChanged().onNotify(this, [this]() {
        emit intervalDirectionChanged(intervalDirection());
    });

    brailleConfiguration()->brailleTableChanged().onNotify(this, [this]() {
        emit brailleTableChanged(brailleTable());
    });
}

bool BraillePreferencesModel::braillePanelEnabled() const
{
    return brailleConfiguration()->braillePanelEnabled();
}

QString BraillePreferencesModel::brailleTable() const
{
    return brailleConfiguration()->brailleTable();
}

int BraillePreferencesModel::intervalDirection() const
{
    return static_cast<int>(brailleConfiguration()->intervalDirection());
}

QStringList BraillePreferencesModel::brailleTables() const
{
    return brailleConfiguration()->brailleTableList();
}

QVariantList BraillePreferencesModel::intervalDirections() const
{
    return QVariantList {
        QVariantMap {
            //: Braille chord interval direction: automatic (based on clef)
            { "text", muse::qtrc("appshell/preferences", "Auto") },
            { "value", static_cast<int>(BrailleIntervalDirection::Auto) },
        },
        QVariantMap {
            //: Braille chord interval direction: up (ascending)
            { "text", muse::qtrc("appshell/preferences", "Up") },
            { "value", static_cast<int>(BrailleIntervalDirection::Up) },
        },
        QVariantMap {
            //: Braille chord interval direction: down (descending)
            { "text", muse::qtrc("appshell/preferences", "Down") },
            { "value", static_cast<int>(BrailleIntervalDirection::Down) },
        },
    };
}

void BraillePreferencesModel::setBraillePanelEnabled(bool value)
{
    if (value == braillePanelEnabled()) {
        return;
    }

    brailleConfiguration()->setBraillePanelEnabled(value);
    emit braillePanelEnabledChanged(value);
}

void BraillePreferencesModel::setBrailleTable(QString table)
{
    if (table == brailleTable()) {
        return;
    }

    brailleConfiguration()->setBrailleTable(table);
    emit brailleTableChanged(table);
}

void BraillePreferencesModel::setIntervalDirection(int direction)
{
    if (direction == intervalDirection()) {
        return;
    }

    brailleConfiguration()->setIntervalDirection(static_cast<BrailleIntervalDirection>(direction));
    emit intervalDirectionChanged(direction);
}
