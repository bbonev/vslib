/*
 *
 * (c) Vladi Belperchinov-Shabanski "Cade" <cade@biscom.net> 1998-1999
 *
 * SEE `README',LICENSE' OR COPYING' FILE FOR LICENSE AND OTHER DETAILS!
 *
 * $Id: eval.h,v 1.2 2001/10/28 13:53:02 cade Exp $
 *
 */
 

#ifndef _EVAL_H_
#define _EVAL_H_

//
// this evaluates math expression with recursive parser etc.
// (c) Vladi Belperchinov-Shabanski "Cade" <cade@biscom.net> 1996-1998
//

extern int EvalResult;
double Eval( const char* pExp );

#endif //_EVAL_H_
