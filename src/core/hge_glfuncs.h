/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** OpenGL entry points.
*/

// don't put #pragma once wrappers in this file, it gets #included
//  several times with different #defines for GL_PROC.

// base GL functionality...
GL_PROC(glEnable,WINGDIAPI,void,(GLenum cap));
GL_PROC(glDisable,WINGDIAPI,void,(GLenum cap));
GL_PROC(glGetIntegerv,WINGDIAPI,void,(GLenum pname, GLint *params));
GL_PROC(glGetString,WINGDIAPI,const GLubyte *,(GLenum name));
GL_PROC(glGetError,WINGDIAPI,GLenum,(void));
GL_PROC(glDepthMask,WINGDIAPI,void,(GLboolean flag));
GL_PROC(glDepthRange,WINGDIAPI,void,(GLclampd zNear, GLclampd zFar));
GL_PROC(glBlendFunc,WINGDIAPI,void,(GLenum sfactor, GLenum dfactor));
GL_PROC(glAlphaFunc,WINGDIAPI,void,(GLenum func, GLclampf ref));
GL_PROC(glDepthFunc,WINGDIAPI,void,(GLenum func));
GL_PROC(glMatrixMode,WINGDIAPI,void,(GLenum mode));
GL_PROC(glLoadIdentity,WINGDIAPI,void,(void));
GL_PROC(glScalef,WINGDIAPI,void,(GLfloat x, GLfloat y, GLfloat z));
GL_PROC(glViewport,WINGDIAPI,void,(GLint x, GLint y, GLsizei width, GLsizei height));
GL_PROC(glTranslatef,WINGDIAPI,void,(GLfloat x, GLfloat y, GLfloat z));
GL_PROC(glRotatef,WINGDIAPI,void,(GLfloat angle, GLfloat x, GLfloat y, GLfloat z));
GL_PROC(glOrtho,WINGDIAPI,void,(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar));
GL_PROC(glScissor,WINGDIAPI,void,(GLint x, GLint y, GLsizei width, GLsizei height));
GL_PROC(glClearColor,WINGDIAPI,void,(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
GL_PROC(glClear,WINGDIAPI,void,(GLbitfield mask));
GL_PROC(glPixelStorei,WINGDIAPI,void,(GLenum pname, GLint param));
GL_PROC(glBindTexture,WINGDIAPI,void,(GLenum target, GLuint texture));
GL_PROC(glTexEnvi,WINGDIAPI,void,(GLenum target, GLenum pname, GLint param));
GL_PROC(glTexParameteri,WINGDIAPI,void,(GLenum target, GLenum pname, GLint param));
GL_PROC(glTexImage2D,WINGDIAPI,void,(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels));
GL_PROC(glTexSubImage2D,WINGDIAPI,void,(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels));
GL_PROC(glGenTextures,WINGDIAPI,void,(GLsizei n, GLuint *textures));
GL_PROC(glDeleteTextures,WINGDIAPI,void,(GLsizei n, const GLuint *textures));
GL_PROC(glVertexPointer,WINGDIAPI,void,(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
GL_PROC(glColorPointer,WINGDIAPI,void,(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
GL_PROC(glTexCoordPointer,WINGDIAPI,void,(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
GL_PROC(glDrawArrays,WINGDIAPI,void,(GLenum mode, GLint first, GLsizei count));
GL_PROC(glDrawElements,WINGDIAPI,void,(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices));
GL_PROC(glEnableClientState,WINGDIAPI,void,(GLenum array));
GL_PROC(glFinish,WINGDIAPI,void,(void));
GL_PROC(glReadPixels,WINGDIAPI,void,(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels));

// GL_EXT_framebuffer_object ...
GL_PROC(glBindRenderbufferEXT,,void,(GLenum target, GLuint name));
GL_PROC(glDeleteRenderbuffersEXT,,void,(GLsizei, const GLuint *));
GL_PROC(glGenRenderbuffersEXT,,void,(GLsizei, GLuint *));
GL_PROC(glRenderbufferStorageEXT,,void,(GLenum, GLenum, GLsizei, GLsizei));
GL_PROC(glBindFramebufferEXT,,void,(GLenum, GLuint));
GL_PROC(glDeleteFramebuffersEXT,,void,(GLsizei, const GLuint *));
GL_PROC(glGenFramebuffersEXT,,void,(GLsizei, GLuint *));
GL_PROC(glCheckFramebufferStatusEXT,,GLenum,(GLenum));
GL_PROC(glFramebufferRenderbufferEXT,,void,(GLenum, GLenum, GLenum, GLuint));
GL_PROC(glFramebufferTexture2DEXT,,void,(GLenum, GLenum, GLenum, GLuint, GLint));

// end of hge_glfuncs.h ...

