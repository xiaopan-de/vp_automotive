/**
 * This file is automatically generated from [XML2SCA]
 * https://github.com/panxiao-tech/XML2SCA
 * Contact: Xiao Pan <pan@cs.uni-kl.de | xml2sca@panxiao.tech>
 *
 * @file    ect_sc/tb/throttle_motor/sc_top.h
 * @author  Xiao Pan (pan@cs.uni-kl.de)
 * @date    00:30:34 Jun  2 2018
 * @section LICENSE License (ADD YOUR LICENSE HERE)
 *
 * @section DESCRIPTION Description (ADD YOUR DESCRIPTION HERE)
 *          DC Motor for Throttle Control
 *
 */


#ifndef sc_top_lsf_h_

#define sc_top_lsf_h_
#include "../../src/sca_dcmotor_em.h"
#include "../../src/config_sim.h"






//! ---------------------------------------------------------------------------
//! @brief stimuli module
//! ---------------------------------------------------------------------------
SCA_TDF_MODULE(sca_tdf_stimuli_lsf)
{
    //! in/output ports
    sca_tdf::sca_out<double> pout_tm;
    sca_tdf::sca_in<double>  pin_w;
    sca_tdf::sca_in<double>  pin_a;

    // constructor
    sca_tdf_stimuli_lsf(sc_core::sc_module_name nm){}

    void set_attributes()
    {
        pout_tm.set_delay(1);
        pout_tm.set_timestep(sc_core::sc_time(gc_t_step, sc_core::SC_SEC ));
    }

    void processing()
    {
        double t_now = sc_core::sc_time_stamp().to_seconds();
        double vs = 1.0 * (sin(2*3.14*t_now*10)) + 1.0;
        pout_tm.write(vs);
    }
};

//! ---------------------------------------------------------------------------
//! @brief testbench toplevel module for  DC motor
//! ---------------------------------------------------------------------------
SC_MODULE(sc_top_lsf)
{
    sca_tdf_stimuli_lsf  *i_stimuli;
    sca_lsf_dcmotor_m      *i_dcmotor;

    sca_tdf::sca_signal<double>  sig_tm;
    sca_tdf::sca_signal<double>  sig_w;
    sca_tdf::sca_signal<double>  sig_a;


    // sample period
    sca_core::sca_time tstep;

    // trace file
    sca_util::sca_trace_file* tf;
    std::string trace_format;


    // Constructor
    sc_top_lsf(sc_core::sc_module_name nm):sc_module(nm)
    {
        // top level instances
        i_stimuli      = new sca_tdf_stimuli_lsf("i_stimuli_2");
        i_stimuli->pout_tm(sig_tm);
        i_stimuli->pin_w(sig_w);
        i_stimuli->pin_a(sig_a);


        i_dcmotor  = new sca_lsf_dcmotor_m("i_dcmotor_lsf");
        i_dcmotor->pin_tm(sig_tm);
        i_dcmotor->pout_w(sig_w);
        i_dcmotor->pout_a(sig_a);

        // trace file
        trace_format = "csv";
        tf = trace_format.compare("vcd") == 0 ?
        sca_util::sca_create_vcd_trace_file("tracefile_dcmotor_tb"):
        sca_util::sca_create_tabular_trace_file("tracefile_dcmotor_tb");

        sca_util::sca_trace(tf, sig_tm, "sig_tm");
        sca_util::sca_trace(tf, sig_w, "sig_w");
        sca_util::sca_trace(tf, sig_a, "sig_a");
    };


    // Destructor
    ~sc_top_lsf()
    {
        if(trace_format.compare("vcd"))
            sca_close_tabular_trace_file(tf);
        else
            sca_close_vcd_trace_file(tf);
    }
};









#endif