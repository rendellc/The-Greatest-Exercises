# This skeleton is valid for both Python 2.7 and Python 3.
# You should be aware of your additional code for compatibility of the Python version of your choice.

import time
import sys
from socket import *

# Get the server hostname and port as command line arguments
if len(sys.argv) != 3:
    print("Usage:", sys.argv[0], "hostname", "port")
    exit(1)


host = sys.argv[1]
port = int(sys.argv[2])
timeout = 1 # seconds
 
# Create UDP client socket
socket = socket(AF_INET, SOCK_DGRAM)
socket.settimeout(timeout)

# Ping for 10 times
total_packets = 10
ping_successes = 0
rtt_sum = 0
rtt_max = -float("inf")
rtt_min = float("inf")
start_time = time.time()
for ptime in range(total_packets):
    # Format the message to be sent as in the Lab description	
    data = "Ping {0} {1}".format(str(ptime), str(time.time()))
    
    try:
	# Record the "sent time"
        sent_time = time.time()

	# Send the UDP packet with the ping message
        socket.sendto(data.encode(), (host,port))

	# Receive the server response
        recv_data, server_addres = socket.recvfrom(2048)
  
	# Record the "received time"
        recv_time = time.time()
        ping_successes += 1

	# Display the server response as an output
        print("Response:", recv_data.decode())
    
	# Round trip time is the difference between sent and received time
        #print("RTT:", 1000*(recv_time - sent_time), "milliseconds\n")
        rtt = recv_time - sent_time
        if rtt < rtt_min:
            rtt_min = rtt
        if rtt > rtt_max:
            rtt_max = rtt

        rtt_sum += rtt
    except:
        # Server does not response
	# Assume the packet is lost
        print("Request timed out")
        continue

# Close the client socket
socket.close()
end_time = time.time()


# Print statistics
loss_rate = 100*(total_packets-ping_successes)/total_packets
total_time = end_time - start_time
rtt_avg = rtt_sum
print("---", host,"ping statistics ---")
print(total_packets, "packets transmitted,", \
        ping_successes, "recieved,", \
        round(loss_rate,1), "%, packet loss, time", \
        round(1000*total_time,2), "ms")
print("rtt min/avg/max = {0}/{1}/{2} ms".format(round(1000*rtt_min,2), round(1000*rtt_avg,2), round(1000*rtt_max,2)))


