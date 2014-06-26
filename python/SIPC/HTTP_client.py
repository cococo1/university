import socket
import re
import sys
import os

host = "mp3lemon.net"
port = 80
buffer = 10240
downloade_directive = "D:/"         #default download directory

client_socket = socket.socket()
client_socket.settimeout(10.0)
try:
    client_socket.connect((host,port))
except socket.gaierror:
    sys.exit("[!] Internet connection FAIL")

def set_downloade_directive(downloade_directive):
    print '[i] Current downloade directive >> '+downloade_directive
    choice_modify_downloade_directive=raw_input("[>] Modif downloade directive? [Y/N]: ")
    if choice_modify_downloade_directive in ['y','Y']:
        downloade_directive= raw_input("[>] Set new directive: ")
        if downloade_directive[-1] != '/':
            downloade_directive += ('/')
        overwrite_downloade_directive = None
        if os.path.isfile(downloade_directive):
            overwrite_downloade_directive = raw_input("[>] Directive already exists, overwrite directive? [Y/N]: ")
        else:
            overwrite_downloade_directive = "Y"
        if not os.path.exists(downloade_directive):
            os.makedirs(downloade_directive)
            print "[i] Directive created >> ", downloade_directive
            return downloade_directive
    elif choice_modify_downloade_directive in ['n','N']:
        return downloade_directive
    else:
        client_socket.close()
        sys.exit("[!] Unable to complay.")

def send_search_request (query_search):
    #client-server search protocol message, in this exemple search for: blink 182

    #GET /search.php?query_search=blink+182 HTTP/1.1
    #Host: mp3lemon.net
    #User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:10.0.2) Gecko/20100101 Firefox/10.0.2
    #Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    #Accept-Language: en-us,en;q=0.5
    #Accept-Encoding: gzip, deflate
    #Connection: keep-alive
    #Referer: http://mp3lemon.net/
    #Cookie: PHPSESSID=dim69tn2lcqd2ou6e1i27p3qs4; MG_382=10; MG_259=9; MG_231=8; MG_1904=7
    #

    #NOTE: this client my ignore same filed, it will not influence the result

    to_send = 'GET /search.php?query_search='
    to_send += query_search.replace(' ','+')
    to_send += ' HTTP/1.1\r\n'
    to_send += 'Host: mp3lemon.net\r\n'
    to_send += 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n'
    to_send += 'Accept-Language: en-us,en;q=0.5\r\n'
    to_send += 'Accept-Encoding: gzip, deflate\r\n'
    to_send += 'Connection: keep-alive\r\n'
    to_send += 'Referer: http://mp3lemon.net/\r\n'
    to_send += '\r\n'
    #print to_send
    client_socket.send(to_send)
    received = ''
    while True:
        try:
            received += client_socket.recv(buffer)
            #print received
        except:
            break
    return received

def extract_track_from_received_list (received_query_search):
    #extarct the list of found, according to the search requeste
    #in the recevied, look for information of this structure:
    #<tr>
    #<td class="list_tracks"><a href="/song/283499/Feeling This">Feeling This</a></td>
    #<td class="list_tracks"><a style="color: #1e1e1e;" href="/artist/18482/">Blink 182</a></td>
    #<td class="list_tracks">2:55</td>
    #<td class="list_tracks">4.00 </td>
    #<td class="list_tracks">192 kbps</td>
    #<td class="list_tracks"><a href="/song/283499/Feeling This">???????</a></td>
    #</tr>

    pattern_title = """<td class="list_tracks"><a href="/song/[0-9]*/.*">(.*)</a></td>"""
    title = re.findall(pattern_title, received_query_search)
    pattern_artist = """<td class="list_tracks"><a .* href="/artist/[0-9]*/">(.*)</a></td>"""
    artist = re.findall(pattern_artist, received_query_search)
    pattern_duration = """<td class="list_tracks">([0-9]*:[0-9]*)"""
    duration = re.findall(pattern_duration, received_query_search)
    pattern_size = """<td class="list_tracks">([0-9]*.[0-9]*)"""
    size = re.findall(pattern_size, received_query_search)
    pattern_bitrate = """<td class="list_tracks">(.* kbps)</td>"""
    bitrate =  re.findall(pattern_bitrate, received_query_search)
    pattern_id = """<td class="list_tracks"><a href="/song/([0-9]*)/.*">.*</a></td>"""
    id_ = re.findall(pattern_id, received_query_search)

    #print len(title)
    #print len(artist)
    #print len(duration)
    #print len(size)
    #print len(bitrate)
    #print len(id_ )

    #make one structured list of all the tracks
    track_list=[]
    j=0
    i=2
    while (i<len(id_)):
        track_list.append(artist[j])
        track_list.append(title[j])
        track_list.append(duration[j])
        track_list.append(size[j])
        track_list.append(bitrate[j])
        track_list.append(id_[j])
        i+=2
        j+=1
    #print track_list
    p=1
    k=0
    while (k<len(track_list)):
        print '[ ',p,' ]',track_list[k],'-',track_list[k+1],'-',track_list[k+2],'-',track_list[k+3],'Mb -',track_list[k+4],'-',track_list[k+5]
        k+=6
        p+=1

    #extract from track list info about the track we want to downloade
    while True:
        download_track = raw_input('[>] Download .mp3: ')
        try:
            download_track = int(download_track)
            if (download_track < (len(track_list)/6) and download_track > 0):
                #obtaine the domain where file is located
                domain=send_get_domain_request( track_list[(download_track*6)-1],track_list[(download_track*6)-5])
                #print domain
                track_info = []
                track_info.append(domain)
                track_info.append(track_list[(download_track*6)-6])
                track_info.append(track_list[(download_track*6)-5])
                track_info.append(track_list[(download_track*6)-4])
                track_info.append(track_list[(download_track*6)-3])
                track_info.append(track_list[(download_track*6)-2])
                track_info.append(track_list[(download_track*6)-1])
                #print track_info
                client_socket.close()
                return track_info
                break
        except:
            print '[>] Retry Download .mp3: '
            continue

def send_get_domain_request (download_request_id,download_request_title):
    #client-server get downloade domain protocol message

    #GET /download.php?idfile=283499 HTTP/1.1
    #Host: mp3lemon.net
    #User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:10.0.2) Gecko/20100101 Firefox/10.0.2
    #Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    #Accept-Language: en-us,en;q=0.5
    #Accept-Encoding: gzip, deflate
    #Connection: keep-alive
    #Referer: http://mp3lemon.net/song/283499/Feeling%20This
    #Cookie: PHPSESSID=dim69tn2lcqd2ou6e1i27p3qs4; MG_382=9; MG_259=8; MG_231=7; MG_1904=6
    #

    #NOTE: this client my ignore same filed, it will not influence the result

    to_send  = 'GET /download.php?idfile='
    to_send += download_request_id
    to_send += ' HTTP/1.1\r\n'
    to_send += 'Host: mp3lemon.net\r\n'
    to_send += 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n'
    to_send += 'Accept-Language: en-us,en;q=0.5\r\n'
    to_send += 'Accept-Encoding: gzip, deflate\r\n'
    to_send += 'Connection: keep-alive\r\n'
    to_send += 'Referer: http://mp3lemon.net/song/'
    to_send += download_request_id+'/'+download_request_title.replace(' ','%20')+'\r\n'
    to_send += '\r\n'
    #print to_send
    client_socket.send(to_send)
    received = ''
    while True:
        try:
            received += client_socket.recv(buffer)
        except:
            break

    #client-server get downloade domain protocol message expected to recive from server

    #HTTP/1.1 302 Found
    #Server: nginx/1.0.11
    #Date: Mon, 12 Mar 2012 11:37:06 GMT
    #Content-Type: text/html; charset=Windows-1251
    #Connection: keep-alive
    #X-Powered-By: PHP/5.3.9
    #Expires: Thu, 19 Nov 1981 08:52:00 GMT
    #Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0
    #Pragma: no-cache
    #Location: http://dl1.zakachali.net/file/283499
    #Content-Length: 0
    #

    pattern_domain = """Location: http://(.*)/file/[1-9]*"""
    domain = re.findall(pattern_domain, received)
    #print domain
    return domain

def send_redirect_link_request (download_request_id,download_request_domain):
    # request a redirect to the link from where to downloade file
    #client-server protocol message:

    #POST /file/283499 HTTP/1.1
    #Host: dl1.zakachali.net
    #User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:10.0.2) Gecko/20100101 Firefox/10.0.2
    #Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    #Accept-Language: en-us,en;q=0.5
    #Accept-Encoding: gzip, deflate
    #Connection: keep-alive
    #Referer: http://dl1.zakachali.net/file/283499
    #Content-Type: application/x-www-form-urlencoded
    #Content-Length: 18
    #
    #rcode=1&site_d=net

    to_send  = 'POST /file/'
    to_send += download_request_id
    to_send += ' HTTP/1.1\r\n'
    to_send += 'Host: '+download_request_domain[0]+'\r\n'
    to_send += 'User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:10.0.2) Gecko/20100101 Firefox/10.0.2\r\n'
    to_send += 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n'
    to_send += 'Accept-Language: en-us,en;q=0.5\r\n'
    to_send += 'Accept-Encoding: gzip, deflate\r\n'
    to_send += 'Connection: keep-alive\r\n'
    to_send += 'Referer: http://'+download_request_domain[0]
    to_send += '/file/'+download_request_id+'\r\n'
    to_send += 'Content-Type: application/x-www-form-urlencoded\r\n'
    to_send += 'Content-Length: 18\r\n'
    to_send += '\r\n'
    to_send += 'rcode=1&site_d=net'
    #print to_send

    download_socket.send(to_send)
    received = ''
    while True:
        try:
            received += download_socket.recv(buffer)
        except:
            break
    #print received

    #in the recieved stream of data we look for the adres of redirect
    pattern_redirect = """">http://.*/download/(.*)</a></td></tr>"""
    redirect = re.findall(pattern_redirect, received)
    #print redirect
    return redirect
################################################################################

def downloade_mp3(downloade_link, domain, artist, title, duration, size, bitrate, id_):
    path=downloade_directive+artist+"_"+title+"_"+duration+"_"+size+" Mb_"+bitrate+".mp3"
    #print path
    track_size=check_file(path)
    mode='wb'

    #GET /download/747db956468773f627fbdb83bdd16768 HTTP/1.1
    #Host: dl1.zakachali.net
    #User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:10.0.2) Gecko/20100101 Firefox/10.0.2
    #Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    #Accept-Language: en-us,en;q=0.5
    #Accept-Encoding: gzip, deflate
    #Connection: keep-alive
    #Referer: http://dl1.zakachali.net/file/283499
    #

    to_send   = 'GET /download/'+downloade_link[0]+' HTTP/1.1\r\n'
    to_send  += 'Host: '+domain[0]+'\r\n'
    to_send  += 'User-Agent: Mozilla/5.0 (Windows NT 5.1; rv:10.0.2) Gecko/20100101 Firefox/10.0.2\r\n'
    to_send  += 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n'
    to_send  += 'Accept-Language: en-us,en;q=0.5\r\n'
    to_send  += 'Accept-Encoding: gzip, deflate\r\n'
    to_send  += 'Connection: keep-alive\r\n'
    to_send  += 'Referer: http://'+domain[0]+'/file/'+id_+'\r\n'
    if track_size>0:
    #if part of file [present, continue copy from that point on
    #to do that we must sent to server a silightly modified header
        to_send  += "Range: bytes=" + str(track_size) + "-\r\n"
        mode='ab'
    to_send  += '\r\n'
    #print to_send

    download_socket.send(to_send)
    received = ''
    while True:
        try:
            received += download_socket.recv(buffer)
        except:
            break
    #print received

    # from server expect te recive a stream containning header like this one:

    #HTTP/1.1 200 OK
    #Server: nginx/1.0.0
    #Date: Mon, 12 Mar 2012 13:37:21 GMT
    #Content-Type: audio/mpeg
    #Connection: keep-alive
    #X-Powered-By: PHP/5.2.6
    #pragma: cache
    #cache-control: public, must-revalidate, max-age=0
    #accept-ranges: bytes
    #x-sent-by: PEAR::HTTP::Download
    #last-modified: Wed, 30 Sep 2009 18:46:23 GMT
    #content-disposition: attachment; filename="Blink_182_-_01_-_Feeling_This[mp3lemon.net].mp3"; filename="Blink_182_-_01_-_Feeling_This.mp3"
    #etag: "0c0676d86ac251a9d7924e89638e1436-250568905"
    #content-length: 4196448
    #Content-Language: windows-1251
    #
    #ID3

    #and the file separated from header with \r\n. separate header from file and write file

    head,track= received.split("\r\n\r\n")
    print track
    track_write(track, path, mode)

def check_file(path):
	try:
		file_size = os.path.getsize(path)
	except os.error:
		return 0
	print "[!] File exists. File size: " ,round(float(file_size)/1048576.0, 2)," Mb"
	return file_size

def track_write(track, path, mode):
	f = open(path, mode)
	f.write(track)
	f.close()

################################################################################
if __name__ == "__main__":
    print '[!] .mp3 downloade from mp3lemon.net Client started'
    search_for = raw_input('[>] Search .mp3: ')
    received_search_for=send_search_request (search_for)
    domain, artist, title, duration, size, bitrate, id_=extract_track_from_received_list(received_search_for)
    print "[>] Downloade .mp3 file: ",artist, title, duration, size, bitrate
    downloade_directive=set_downloade_directive(downloade_directive)

    download_socket = socket.socket()
    download_socket.settimeout(30.0)
    try:
        download_socket.connect((domain[0],port))
    except socket.gaierror:
        sys.exit("[!] Internet connection FAIL")

    downloade_link=send_redirect_link_request (id_,domain)
    downloade_mp3(downloade_link, domain, artist, title, duration, size, bitrate, id_)
    download_socket.close()
    sys.exit("[!] Downloade complete.")
