// cue.cpp
// Created 10/26/2009 by RJ Ryan (rryan@mit.edu)

#include <QMutexLocker>
#include <QtDebug>

#include "library/dao/cue.h"

Cue::~Cue() {
    qDebug() << "~Cue()" << m_iId;
}

Cue::Cue(int trackId)
        : m_bDirty(false),
          m_iId(-1),
          m_iTrackId(trackId),
          m_type(INVALID),
          m_iPosition(-1),
          m_iLength(0),
          m_iHotCue(-1),
          m_label("") {
}


Cue::Cue(int id, int trackId, Cue::CueType type, int position, int length,
         int hotCue, QString label)
        : m_bDirty(false),
          m_iId(id),
          m_iTrackId(trackId),
          m_type(type),
          m_iPosition(position),
          m_iLength(length),
          m_iHotCue(hotCue),
          m_label(label) {
}

int Cue::getId() {
    QMutexLocker lock(&m_mutex);
    return m_iId;
}

void Cue::setId(int cueId) {
    QMutexLocker lock(&m_mutex);
    m_iId = cueId;
    m_bDirty = true;
    lock.unlock();
    emit(updated());
}

int Cue::getTrackId() {
    QMutexLocker lock(&m_mutex);
    return m_iTrackId;
}

void Cue::setTrackId(int trackId) {
    QMutexLocker lock(&m_mutex);
    m_iTrackId = trackId;
    m_bDirty = true;
    lock.unlock();
    emit(updated());
}

Cue::CueType Cue::getType() {
    QMutexLocker lock(&m_mutex);
    return m_type;
}

void Cue::setType(Cue::CueType type) {
    QMutexLocker lock(&m_mutex);
    m_type = type;
    m_bDirty = true;
    lock.unlock();
    emit(updated());
}

int Cue::getPosition() {
    QMutexLocker lock(&m_mutex);
    return m_iPosition;
}

void Cue::setPosition(int position) {
    QMutexLocker lock(&m_mutex);
    Q_ASSERT(position % 2 == 0);
    m_iPosition = position;
    m_bDirty = true;
    lock.unlock();
    emit(updated());
}

int Cue::getLength() {
    QMutexLocker lock(&m_mutex);
    return m_iLength;
}

void Cue::setLength(int length) {
    QMutexLocker lock(&m_mutex);
    Q_ASSERT(length % 2 == 0);
    m_iLength = length;
    m_bDirty = true;
    lock.unlock();
    emit(updated());
}

int Cue::getHotCue() {
    QMutexLocker lock(&m_mutex);
    return m_iHotCue;
}

void Cue::setHotCue(int hotCue) {
    QMutexLocker lock(&m_mutex);
    // TODO(XXX) enforce uniqueness?
    m_iHotCue = hotCue;
    m_bDirty = true;
    lock.unlock();
    emit(updated());
}

const QString& Cue::getLabel() {
    QMutexLocker lock(&m_mutex);
    return m_label;
}

void Cue::setLabel(const QString& label) {
    QMutexLocker lock(&m_mutex);
    m_label = label;
    m_bDirty = true;
    lock.unlock();
    emit(updated());
}

bool Cue::isDirty() {
    QMutexLocker lock(&m_mutex);
    return m_bDirty;
}

void Cue::setDirty(bool dirty) {
    QMutexLocker lock(&m_mutex);
    m_bDirty = dirty;
}
