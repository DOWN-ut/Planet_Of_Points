/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <QtMath>
GLWidget* GLWidget::instance = nullptr;

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0),
      m_pos(QVector3D(0,0,20)),
      m_xTranslation(0),
      m_yTranslation(0),
      m_zTranslation(0),
      timeScale(1), paused(false),

      grid(Grid(30,75)),
      gridDisplayMode(0),
      particlesDisplayMode(0),
      particlesDisplayAttributs(0),
      m_program(0)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }

    setFocusPolicy(Qt::StrongFocus);

    moveStep = 7;
    deltaTime = 0.05;

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&GLWidget::updateAll);
    timer->start(deltaTime);

    instance = this;
}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::updateAll()
{
    m_pos += QVector3D(
                (m_xTranslation * cos( (m_yRot / 5700.0f) * 2 * M_PI)) + (-m_zTranslation * sin( (m_yRot / 5700.0f) * 2 * M_PI)),
                m_yTranslation,// * cos( (m_yRot / 5700.0f) * 2 * M_PI),
                (m_zTranslation * cos( (m_yRot / 5700.0f) * 2 * M_PI)) + (m_xTranslation * sin( (m_yRot / 5700.0f) * 2 * M_PI)) ); //(cameraFront * m_zTranslation) + (cameraUp * m_yTranslation) + (cameraRight * m_xTranslation);
    //cout << m_pos.x() << " " << m_pos.y() << " " << m_pos.z() << endl;
    cout << m_xRot << "  " << m_yRot << "  " << m_zRot << "    " << cos( (m_yRot / 5700.0f) * 2 * M_PI) <<  endl;

    cout << "Update" << endl;

    grid.update(deltaTime);
    m_points.update(deltaTime);

    timer->setInterval(deltaTime * timeScale);

    update();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        //Completer pour emettre un signal
        emit changedXRotation(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        //Completer pour emettre un signal
        emit changedYRotation(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        //Completer pour emettre un signal
        emit changedZRotation(angle);
        update();
    }
}

void GLWidget::move(QVector3D v)
{

    float speed = 1;
    m_xTranslation = moveStep * v.x() * speed * deltaTime;
    m_yTranslation = moveStep * v.y()* speed * deltaTime;
    m_zTranslation = moveStep * v.z()* speed * deltaTime;

}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case  Qt::Key_Z : move(QVector3D(0,0,-1)); break;
    case  Qt::Key_S : move(QVector3D(0,0,1)); break;
    case  Qt::Key_Q : move(QVector3D(1,0,0)); break;
    case  Qt::Key_D : move(QVector3D(-1,0,0)); break;
    case  Qt::Key_Space : move(QVector3D(0,1,0)); break;
    case  Qt::Key_Shift : move(QVector3D(0,-1,0)); break;
    case Qt::Key_Enter: paused = !paused; if(paused) { timer->stop(); } else{timer->start();} break;

    case Qt::Key_G: gridDisplayMode++; if(gridDisplayMode > 2){gridDisplayMode = 0;} break;
    case Qt::Key_P: particlesDisplayMode++; if(particlesDisplayMode > 3){particlesDisplayMode=0;}break;
    case Qt::Key_O: particlesDisplayAttributs++; if(particlesDisplayAttributs > 1){particlesDisplayAttributs=0;}break;
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case  Qt::Key_Z : m_zTranslation = 0; break;
    case  Qt::Key_S : m_zTranslation = 0; break;
    case  Qt::Key_Q : m_xTranslation = 0; break;
    case  Qt::Key_D : m_xTranslation = 0; break;
    case  Qt::Key_Space : m_yTranslation = 0; break;
    case  Qt::Key_Shift : m_yTranslation = 0; break;
    }
}

void GLWidget::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_logoVbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

void GLWidget::setDrawColor(QVector3D color, float alpha)
{
    instance->m_program->setUniformValue(instance->color_location, QVector4D(color.x(),color.y(),color.z(),alpha));
}

void GLWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    cout << "Initialising GL" << endl;
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0,0.0,0.0,0.0);

    m_program = new QOpenGLShaderProgram;
    // Compile vertex shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);

    // Link shader pipeline
    if (!m_program->link())
        close();

    // Bind shader pipeline for use
    if (!m_program->bind())
        close();

    m_mvp_matrix_loc = m_program->uniformLocation("mvp_matrix");
    m_normal_matrix_loc = m_program->uniformLocation("normal_matrix");
    m_light_pos_loc = m_program->uniformLocation("light_position");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    //m_logoVbo.create();
    //m_logoVbo.bind();
    //m_logoVbo.allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

    // Setup our vertex buffer object.
    /*m_meshVbo.create();
    m_meshVbo.bind();
    m_meshVbo.allocate(m_mesh.getRawVertices(), m_mesh.verticesCount() * 3 * sizeof(GLfloat));

    m_meshIndex.create();
    m_meshIndex.bind();
    m_meshIndex.allocate(m_mesh.getRawTriangles(), m_mesh.rawTrianglesCount() * sizeof(GLint));*/

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    color_location = m_program->uniformLocation("color");
    camera_location = m_program->uniformLocation("camera");

    // Our camera never changes in this example.
    m_view.setToIdentity();
    m_view.translate(0, 0, -1);

    // Light position is fixed.
    //m_program->setUniformValue(m_light_pos_loc, QVector3D(0, 0, 70));

    m_points.initGL(m_program);

    //m_program->release();

    cout << "  > Initialised GL" << endl;
}

void GLWidget::setupVertexAttribs()
{
    m_logoVbo.bind();

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    m_logoVbo.release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_model.setToIdentity();
    m_model.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    m_model.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_model.rotate(m_zRot / 16.0f, 0, 0, 1);

    m_model.translate(m_pos.x(),m_pos.y(),m_pos.z());

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();

    // Set modelview-projection matrix
    m_program->setUniformValue(m_mvp_matrix_loc, m_projection * m_view * m_model);
    QMatrix3x3 normal_matrix = m_model.normalMatrix();

    // Set normal matrix
    m_program->setUniformValue(m_normal_matrix_loc, normal_matrix);
    m_program->setUniformValue(camera_location, m_pos);

    //glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());

    m_points.paintGL(m_program, particlesDisplayMode, particlesDisplayAttributs);
    grid.paintGL(m_program,gridDisplayMode);

    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_last_position = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_last_position.x();
    int dy = event->y() - m_last_position.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);

        yaw += dx;
        pitch -= dy;
        pitch = qBound(-89.0f,pitch,89.0f);
        updateCameraVectors();

    } else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_last_position = event->pos();
}
void GLWidget::updateCameraVectors()
{

    // Calculate the new camera front vector
        QVector3D newFront;
        newFront.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        newFront.setY(sin(qDegreesToRadians(pitch)));
        newFront.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        cameraFront = newFront.normalized();

        cameraRight = QVector3D::crossProduct(cameraFront, QVector3D(0.0f, 1.0f, 0.0f)).normalized();
        cameraUp = QVector3D::crossProduct(cameraRight, cameraFront).normalized();
    }
