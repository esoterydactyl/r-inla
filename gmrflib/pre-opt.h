
/* pre-opt.h
 * 
 * Copyright (C) 2021-2021 Havard Rue
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * The author's contact information:
 *
 *        Haavard Rue
 *        CEMSE Division
 *        King Abdullah University of Science and Technology
 *        Thuwal 23955-6900, Saudi Arabia
 *        Email: haavard.rue@kaust.edu.sa
 *        Office: +966 (0)12 808 0640
 *
 *
 */

#ifndef __GMRFLib_PREOPT_H__
#define __GMRFLib_PREOPT_H__

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS					       /* empty */
#define __END_DECLS					       /* empty */
#endif

__BEGIN_DECLS

/* 
 * 
 */
    typedef enum {
	GMRFLib_PREOPT_TP_F = 1,
	GMRFLib_PREOPT_TP_BETA,
	GMRFLib_PREOPT_TP___VOID = -1
} GMRFLib_preopt_type_types_tp;

typedef struct {
	GMRFLib_preopt_type_types_tp tp;
	int idx;
	int tp_idx;
} GMRFLib_preopt_type_tp;

typedef struct {
	int npred;
	int n;
	int nf;
	int nbeta;

	GMRFLib_graph_tp *preopt_graph;
	GMRFLib_Qfunc_tp *preopt_Qfunc;
	void *preopt_Qfunc_arg;

	GMRFLib_graph_tp *latent_graph;			       
	GMRFLib_Qfunc_tp *latent_Qfunc;
	void *latent_Qfunc_arg;
	GMRFLib_constr_tp *latent_constr;

	GMRFLib_graph_tp *like_graph;			       
	GMRFLib_Qfunc_tp *like_Qfunc;
	void *like_Qfunc_arg;

	GMRFLib_bfunc_tp **bfunc;
	double **like_c;	
	double **like_b;	
	double **total_b;	
	double *total_const;	

	int *idx_map_beta;
	int *idx_map_f;

	double **covariate;
	double *prior_precision;

	GMRFLib_Qfunc_tp ***ff_Qfunc;			       /* interaction */
	GMRFLib_Qfunc_tp **f_Qfunc;
	GMRFLib_graph_tp **f_graph;
	double *f_diag;
	GMRFLib_preopt_type_tp *what_type;
	void ***ff_Qfunc_arg;
	void **f_Qfunc_arg;

	GMRFLib_idxval_tp **A_idxval;
	GMRFLib_idxval_tp **At_idxval;
	GMRFLib_idxval_tp ***AtA_idxval;

	double *mode_theta;
	double *mode_x;
} GMRFLib_preopt_tp;

GMRFLib_preopt_type_tp GMRFLib_preopt_what_type(int node, GMRFLib_preopt_tp * a);
double GMRFLib_preopt_Qfunc(int node, int nnode, double *UNUSED(values), void *arg);
double GMRFLib_preopt_latent_Qfunc(int node, int nnode, double *values, void *arg);
double GMRFLib_preopt_like_Qfunc(int node, int nnode, double *values, void *arg);
int GMRFLib_free_preopt(GMRFLib_preopt_tp * preopt);
int GMRFLib_preopt_bnew(double *b, double *constant, GMRFLib_preopt_tp * preopt);
int GMRFLib_preopt_bnew_latent(double *bnew, double *constant, int n, GMRFLib_bfunc_tp ** bfunc);
int GMRFLib_preopt_bnew_like(double *bnew, double *blike, GMRFLib_preopt_tp * arg);
int GMRFLib_preopt_init(GMRFLib_preopt_tp ** preopt, int n, int nf, int **c, double **w,
			GMRFLib_graph_tp ** f_graph, GMRFLib_Qfunc_tp ** f_Qfunc,
			void **f_Qfunc_arg, char *f_sumzero, GMRFLib_constr_tp ** f_constr,
			double *f_diag, 
			GMRFLib_Qfunc_tp *** ff_Qfunc, void ***ff_Qfunc_arg,
			int nbeta, double **covariate, double *prior_precision,
			GMRFLib_bfunc_tp ** bfunc, GMRFLib_ai_param_tp * UNUSED(ai_par));
int GMRFLib_preopt_predictor(double *predictor, double *latent, GMRFLib_preopt_tp * preopt);
int GMRFLib_preopt_test(GMRFLib_preopt_tp * preopt);
int GMRFLib_preopt_update(GMRFLib_preopt_tp * preopt, double *like_b, double *like_c);

__END_DECLS
#endif