#ifndef ADT_EVENT_H_
#define ADT_EVENT_H_

typedef unsigned short au_event_t;

enum {
	ADT_SUCCESS = 0,
	ADT_FAILURE,
	ADT_FAIL_VALUE_AUTH
};

enum {
	ADT_nothing,
	ADT_smf_attach_snap,
	ADT_smf_change_prop,
	ADT_smf_clear,
	ADT_smf_create,
	ADT_smf_create_npg,
	ADT_smf_create_pg,
	ADT_smf_create_prop,
	ADT_smf_create_snap,
	ADT_smf_degrade,
	ADT_smf_delete,
	ADT_smf_delete_npg,
	ADT_smf_delete_pg,
	ADT_smf_delete_prop,
	ADT_smf_delete_snap,
	ADT_smf_disable,
	ADT_smf_enable,
	ADT_smf_immediate_degrade,
	ADT_smf_immediate_maintenance,
	ADT_smf_immtmp_maintenance,
	ADT_smf_maintenance,
	ADT_smf_milestone,
	ADT_smf_read_prop,
	ADT_smf_refresh,
	ADT_smf_restart,
	ADT_smf_tmp_disable,
	ADT_smf_tmp_enable,
	ADT_smf_tmp_maintenance
};

#endif /* ADT_EVENT_H_ */
