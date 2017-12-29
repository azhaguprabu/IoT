### MQTT installation on ubuntu

```
	#apt-get install mosquitto mosquitto-clients
	#mosquitto_passwd -c /etc/mosquitto/passwd prabu
	#vim /etc/mosquitto/conf.d/default.conf

		> allow_anonymous false
		> password_file /etc/mosquitto/passwd
	#systemctl restart mosquitto
```

## Testing

``` #mosquitto_sub -h localhost -t "esp/test" -u "prabu" -P "xxxx"
```

``` #mosquitto_pub -h localhost -t "esp/test" -m "hello world" -u "prabu" -P "xxxx"
```
