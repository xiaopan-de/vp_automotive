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


#ifndef sc_top_h_

#define sc_top_h_
#include "../../src/sca_dtdf_app_sensor.h"


//!
//! @brief stimuli module
//!
SCA_TDF_MODULE(sca_tdf_stimuli)
{
	 sca_tdf::sca_in<double>   pin;

	// constructor
	sca_tdf_stimuli(sc_core::sc_module_name nm){}

    void set_attributes()
    {
        accept_attribute_changes();
        pin.set_delay(1);
    }

	void processing()
	{

     
	}
};


//! 
//! @brief testbench toplevel module
//! 
SC_MODULE(sc_top) 
{
    std::shared_ptr<sca_tdf_stimuli>         i_stimuli;
    std::shared_ptr<sca_dtdf_app_sensor>     i_app_sensor;

	sca_tdf::sca_signal<double>            sig_from_app_sensor;

	// sample period
	sca_core::sca_time tstep;

	// trace file
	sca_util::sca_trace_file* tf;
	std::string trace_format; 


	// Constructor
	sc_top(sc_core::sc_module_name nm):sc_module(nm)
	{ 

		// get time step from json configuration file  
        static const sca_core::sca_time t_step = sca_core::sca_time(20, sc_core::SC_US);

        std::vector<double> sensor_sig {
            0.0, 0.5,
            0.3, 0.7,
            0.6, 1.2,
            0.9, 0.3,
            1.2, 0.7,
            1.5, 0.3,
            1.8, 0.7,
            2.1, 0.0
        };
        
		// top level instances
        i_stimuli       = std::make_shared<sca_tdf_stimuli>("i_stimuli");
		i_app_sensor    = std::make_shared<sca_dtdf_app_sensor>("i_app_sensor",
                                                               sensor_sig);

		// interconnections 
		i_app_sensor->pout(sig_from_app_sensor);
		i_stimuli->pin(sig_from_app_sensor);
		

        // setup timestep
		i_stimuli->set_timestep(t_step);
        
        // trace file
        trace_format = "vcd";
        tf = trace_format.compare("vcd") == 0 ?
        sca_util::sca_create_vcd_trace_file("tracefile_app_sensor_tb"):
        sca_util::sca_create_tabular_trace_file("tracefile_app_sensor_tb");
        
		sca_util::sca_trace(tf, sig_from_app_sensor, "sig_from_app_sensor");

	};


	// Destructor
	~sc_top()
	{
		if(trace_format.compare("vcd")) 
			 sca_close_tabular_trace_file(tf);
		 else
			 sca_close_vcd_trace_file(tf);
	}


};

#endif 