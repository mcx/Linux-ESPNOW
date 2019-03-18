#include "ESPNOW_types.h"

#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>

void ESPNOW_packet::set_channel(uint16_t channel_freq) {
this->radiotap.channel_freq = channel_freq;
}

void ESPNOW_packet::set_datarate(uint8_t datarateMHz) {
	this->radiotap.datarate = datarateMHz;
}

void ESPNOW_packet::set_my_mac(uint8_t my_mac[6]) {
	memcpy(this->wlan.sa, my_mac, sizeof(uint8_t)*6);
}

void ESPNOW_packet::set_dst_mac(uint8_t dst_mac[6]) {
	memcpy(this->wlan.da, dst_mac, sizeof(uint8_t)*6);
	memcpy(this->wlan.bssid, dst_mac, sizeof(uint8_t)*6);
}

int ESPNOW_packet::toBytes(uint8_t *bytes, int max_len) {	
	int correct_len = sizeof(ESPNOW_packet) + this->wlan.actionframe.content.length - 0xff;
	
	assert(correct_len <= max_len); 

	memcpy(bytes, this, correct_len);	
	
	memcpy(bytes + correct_len - sizeof(this->wlan.fcs), &(this->wlan.fcs), sizeof(this->wlan.fcs));

	return correct_len;
}