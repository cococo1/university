class CommunicationFrame(object):
	"""
	TYhis vclass
	"""
	def __init__(self, *args, **kwargs):
		log.info('CommunicationFrame :: __init__() : IN')
		
		self.ProtocolTemplateDict = None
		self.MeterConfigDict = None
		self.DictionariesBlueprint()
		
		if 'LoadSourceType' in kwargs:
			log.info('CommunicationFrame :: __init__() : Load Source Type is %s', kwargs['LoadSourceType'])
		else:
			Error = 'Missing Load Source Type'
			log.error('CommunicationFrame :: __init__() : Error = %s', Error)
			raise RuntimeError, Error

		if 'MeterName' in kwargs:
			log.info('CommunicationFrame :: __init__() : Meter Name is %s', kwargs['MeterName'])
		elif 'MeterConfigDict' in kwargs:
			log.info('CommunicationFrame :: __init__() : Meter Config Dict is in kwargs')
		else:
			Error = 'Missing Meter Name or MeterConfigDict'
			log.error('CommunicationFrame :: __init__() : Error = %s', Error)
			raise RuntimeError, Error
			
		if 'MeterConfigPath' in kwargs:
			log.info('CommunicationFrame :: __init__() : Load Meter Config Dictionary')
			self.MeterConfigDict = self.DictionaryLoad(
				dictType='MeterConfigDict',
				sourceType=kwargs['LoadSourceType'],
				path=kwargs['MeterConfigPath'],
				meterName=kwargs['MeterName'])
		elif 'MeterConfigDict' in kwargs:
			log.info('CommunicationFrame :: __init__() : Assign Meter Config Dictionary')
			self.MeterConfigDict = kwargs['MeterConfigDict']
		else:
			Error = 'Missing Meter Config Dictionary'
			log.error('CommunicationFrame :: __init__() : Error = %s', Error)
			raise RuntimeError, Error

		self.SanityCheckMeterConfigDict(self.MeterConfigDict)
		
		if 'ProtocolTemplatePath' in kwargs:
			log.info('CommunicationFrame :: __init__() : Load Protocol Template Dictionary')
			self.ProtocolTemplateDict = self.DictionaryLoad(
				dictType='ProtocolTemplateDict',
				sourceType=kwargs['LoadSourceType'],
				path=kwargs['ProtocolTemplatePath'])
		elif 'ProtocolTemplateDict' in kwargs:
			log.info('CommunicationFrame :: __init__() : Assign Protocol Template Dictionary')
			self.ProtocolTemplateDict = kwargs['ProtocolTemplateDict']
		else:
			Error = 'Missing Protocol Template Dictionary'
			log.error('CommunicationFrame :: __init__() : Error = %s', Error)
			raise RuntimeError, Error

		self.SanityCheckProtocolTemplateDict(self.ProtocolTemplateDict)
		
		log.info('CommunicationFrame :: __init__() : OUT')

	def __del__(self):
		log.info('CommunicationFrame :: __del__() : IN')
		
		del self.ProtocolTemplateDict
		del self.MeterConfigDict
		
		log.info('CommunicationFrame :: __del__() : OUT')

	def DictionariesBlueprint(self):
		log.info('CommunicationFrame :: DictionariesBlueprint() : IN')
		
		# Protocol Template Dict
		self.BlueprintProtocolTemplateDict = {}
		self.BlueprintProtocolTemplateDict['CmdInfo'] = [str]
		self.BlueprintProtocolTemplateDict['SetUp'] = [dict]
		self.BlueprintProtocolTemplateDict['SendDataStr'] = [str]
		self.BlueprintProtocolTemplateDict['ReceivedData'] = ['pack', 'be_pack', 'le_pack', 'be_eval_pack', 'le_eval_pack', 'return', 'retry']
		
		# Meter Config Dict
		self.BlueprintMeterConfigDict = {}
		self.BlueprintMeterConfigDict['Communication'] = {}
		self.BlueprintMeterConfigDict['Communication']['CRC'] = ['CRC16_Modbus_LittleEndian', 'CRC16_Modbus_BigEndian','NO_CRC']
		self.BlueprintMeterConfigDict['Communication']['Echo'] = [True, False]
		self.BlueprintMeterConfigDict['Communication']['MaxDepth'] = (range(0, 101), 'From the rage 0 to 100.')
		self.BlueprintMeterConfigDict['Communication']['MaxTry'] = (range(0, 101), 'From the rage 0 to 100.')
		self.BlueprintMeterConfigDict['Connection'] = {}
		self.BlueprintMeterConfigDict['Connection']['Type'] = ['Port', 'Socket', 'UnixSocket']
		self.BlueprintMeterConfigDict['Connection']['SetUp'] = {}
		self.BlueprintMeterConfigDict['Values'] = ['Raw', 'SingleDigitStr', 'DoubleDigitStr']
		
		# Port Communication SetUp
		self.BlueprintPortSetUp = {}
		
		PortName = '/dev/ttyUSB'
		PortRange = []
		for i in range(0, 257): PortRange.append(PortName + str(i))
		PortInfo = 'From the rage ' + PortName + '0 to ' + PortName + '256.'
		
		self.BlueprintPortSetUp['port'] = (PortRange, PortInfo)
		self.BlueprintPortSetUp['baudrate'] = ([50, 75, 110, 134, 150, 200, 300, 600, 1200,
												1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200], 'From the rage of the standard values: [50 ... 115200].')
		#self.BlueprintPortSetUp['baudrate'] = (range(50, 4000001), 'From the rage 50 to 4000001.')
		self.BlueprintPortSetUp['bytesize'] = [5, 6, 7, 8]
		self.BlueprintPortSetUp['parity'] = ['N', 'E', 'O', 'M', 'S', 'None', 'Even', 'Odd', 'Mark', 'Space', ]
		self.BlueprintPortSetUp['stopbits'] = [1, 1.5, 2]
		self.BlueprintPortSetUp['EOF'] = [0x00, 0x01]
		self.BlueprintPortSetUp['error'] = [0x00, 0x01]
		self.BlueprintPortSetUp['break'] = [0x00, 0x01]
		self.BlueprintPortSetUp['event'] = [0x00, 0x01]
		self.BlueprintPortSetUp['xonxoff'] = [True, False]
		self.BlueprintPortSetUp['XON'] = [0x00, 0x01]
		self.BlueprintPortSetUp['XOF'] = [0x00, 0x01]
		self.BlueprintPortSetUp['rtscts'] = [True, False]
		self.BlueprintPortSetUp['dsrdtr'] = [True, False]
		self.BlueprintPortSetUp['timeout'] = (range(0, 216001), 'From the rage 0 to 216000.')
		self.BlueprintPortSetUp['writeTimeout'] = (range(0, 216001), 'From the rage 0 to 216000.')
		self.BlueprintPortSetUp['interCharTimeout'] = [0x00, 0x01]
		
		# Socket Communication SetUp
		
		self.BlueprintSocketSetUp = {}
		
		log.info('CommunicationFrame :: DictionariesBlueprint() : OUT')

	def DictionaryLoad(self, *args, **kwargs):
		log.info('CommunicationFrame :: DictionaryLoad() : IN')
		
		try:
			sourceType = kwargs['sourceType']
		except:
			Error = 'Load Source Type is Missing'
			log.error('CommunicationFrame :: DictionaryLoad() : Error = %s', Error)
			raise RuntimeError, Error
			
		if 'yaml' == sourceType:
			RetLoadedDict = self.YamlLoadDictionary(**kwargs)
		elif '' == sourceType:
			# for future Type`s of loading
			pass
		
		else:
			Error = 'Load Source Type is Unknown'
			log.error('CommunicationFrame :: DictionaryLoad() : Error = %s', Error)
			raise RuntimeError, Error

		log.info('CommunicationFrame :: DictionaryLoad() : OUT')
		return RetLoadedDict

	def SanityCheckMeterConfigDict(self, MeterConfigDict=None):
		log.info('CommunicationFrame :: SanityCheckMeterConfigDict() : IN')
		
		if not MeterConfigDict:
			Error = 'MeterConfigDict is None'
			log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
			raise RuntimeError, Error
			#pp.pprint(MeterConfigDict)
		
		for meterCofigKey, meterCofigValue in MeterConfigDict.iteritems():
			if meterCofigKey not in self.BlueprintMeterConfigDict.keys():
				templateStr = Template('MeterConfigDict[$meterCofigKey] = $meterCofigValue')
				substituteDict = {'meterCofigKey': meterCofigKey, 'meterCofigValue': meterCofigValue}
				Error = Template.substitute(templateStr, substituteDict)
				templateStr = Template(', Unexpected Key. Expected Key: $expectedKey')
				substituteDict = {'expectedKey': self.BlueprintMeterConfigDict.keys()}
				Error += Template.substitute(templateStr, substituteDict)
				log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
				raise RuntimeError, Error

			if meterCofigKey == 'Communication':
				for commKey, commValue in meterCofigValue.iteritems():
					
					if commKey not in self.BlueprintMeterConfigDict['Communication'].keys():
						# ---------- Error ----------
						templateStr = Template('MeterConfigDict[$meterCofigKey][$commKey] = $commValue')
						substituteDict = {'meterCofigKey': meterCofigKey, 'commKey': commKey, 'commValue': commValue}
						Error = Template.substitute(templateStr, substituteDict)
						templateStr = Template(', Unexpected Key. Expected Key: $expectedKey')
						substituteDict = {'expectedKey': self.BlueprintMeterConfigDict['Communication'].keys()}
						Error += Template.substitute(templateStr, substituteDict)
						log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
						raise RuntimeError, Error
						
					# in order not to have big ranges in the Error Info string
					ErrorInfoData = self.BlueprintMeterConfigDict['Communication'][commKey]
					if type(ErrorInfoData) == tuple:
						(ErrorData, ErrorInfo) = ErrorInfoData
						ErrorInfoDataSubstituteDict = {'expectedValue': ErrorInfo}
					else:
						ErrorData = ErrorInfoData
						ErrorInfoDataSubstituteDict = {'expectedValue': ErrorInfoData}
						
					if commValue not in ErrorData:
						# ---------- Error ----------
						templateStr = Template('MeterConfigDict[$meterCofigKey][$commKey] = $commValue')
						substituteDict = {'meterCofigKey': meterCofigKey, 'commKey': commKey, 'commValue': commValue}
						Error = Template.substitute(templateStr, substituteDict)
						templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
						Error += Template.substitute(templateStr, ErrorInfoDataSubstituteDict)
						log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
						raise RuntimeError, Error
			elif meterCofigKey == 'Connection':
				for connKey, connValue in meterCofigValue.iteritems():
					
					if connKey not in self.BlueprintMeterConfigDict['Connection'].keys():
						# ---------- Error ----------
						templateStr = Template('MeterConfigDict[$meterCofigKey][$connKey] = $commValue')
						substituteDict = {'meterCofigKey': meterCofigKey, 'connKey': connKey, 'commValue': commValue}
						Error = Template.substitute(templateStr, substituteDict)
						templateStr = Template(', Unexpected Key. Expected Key: $expectedKey')
						substituteDict = {'expectedKey': self.BlueprintMeterConfigDict['Communication'].keys()}
						Error += Template.substitute(templateStr, substituteDict)
						log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
						raise RuntimeError, Error
						
					if connKey == 'Type':
						if connValue not in self.BlueprintMeterConfigDict['Connection']['Type']:
							# ---------- Error ----------
							templateStr = Template('MeterConfigDict[$meterCofigKey][$connKey] = $commValue')
							substituteDict = {'meterCofigKey': meterCofigKey, 'connKey': connKey,
											  'commValue': commValue}
							Error = Template.substitute(templateStr, substituteDict)
							templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
							substituteDict = {'expectedValue': self.BlueprintMeterConfigDict['Connection']['Type']}
							Error += Template.substitute(templateStr, substituteDict)
							log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
							raise RuntimeError, Error
					
					elif connKey == 'SetUp':
						
						if type(connValue) == dict:
							for setupKey, setupValue in connValue.iteritems():
								
								if setupKey not in self.BlueprintPortSetUp.keys():
									# ---------- Error ----------
									templateStr = Template(
										'MeterConfigDict[$meterCofigKey][$connKey][$setupKey] = $setupValue')
									substituteDict = {'meterCofigKey': meterCofigKey, 'connKey': connKey,
													  'setupKey': setupKey, 'setupValue': setupValue}
									Error = Template.substitute(templateStr, substituteDict)
									templateStr = Template(', Unexpected Key. Expected Key: $expectedKey')
									substituteDict = {'expectedKey': self.BlueprintPortSetUp.keys()}
									Error += Template.substitute(templateStr, substituteDict)
									log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
									raise RuntimeError, Error
									
								# in order not to have big ranges in the Error Info string
								ErrorInfoData = self.BlueprintPortSetUp[setupKey]
								if type(ErrorInfoData) == tuple:
									(ErrorData, ErrorInfo) = ErrorInfoData
									ErrorInfoDataSubstituteDict = {'expectedValue': ErrorInfo}
								else:
									ErrorData = ErrorInfoData
									ErrorInfoDataSubstituteDict = {'expectedValue': ErrorInfoData}
									
								if setupValue not in ErrorData:
									# ---------- Error ----------
									templateStr = Template(
										'MeterConfigDict[$meterCofigKey][$connKey][$setupKey] = $setupValue')
									substituteDict = {'meterCofigKey': meterCofigKey, 'connKey': connKey,
													  'setupKey': setupKey, 'setupValue': setupValue}
									Error = Template.substitute(templateStr, substituteDict)
									templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
									Error += Template.substitute(templateStr, ErrorInfoDataSubstituteDict)
									log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
									raise RuntimeError, Error
						
						else:
							# ---------- Error ----------
							templateStr = Template('MeterConfigDict[$meterCofigKey][$connKey] = $connValue')
							substituteDict = {'meterCofigKey': meterCofigKey, 'connKey': connKey,
											  'connValue': connValue}
							Error = Template.substitute(templateStr, substituteDict)
							Error += ', Unexpected Value Type. Expected Value Type: dict'
							log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
							raise RuntimeError, Error
							raise RuntimeError, Error
					
					else:
						# ---------- Error ----------
						templateStr = Template('MeterConfigDict[$meterCofigKey][$connKey] = $commValue')
						substituteDict = {'meterCofigKey': meterCofigKey, 'connKey': connKey, 'commValue': commValue}
						Error = Template.substitute(templateStr, substituteDict)
						Error += 'No implementation of SanityCheck for this Key!'
						log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
						raise RuntimeError, Error
			elif meterCofigKey == 'Values':
				for valKey, valValue in meterCofigValue.iteritems():
					try:
						assert type(valValue) == tuple
						(first, second) = valValue
						assert second in self.BlueprintMeterConfigDict['Values']
					except:
						# ---------- Error ----------
						templateStr = Template('MeterConfigDict[$meterCofigKey][$valKey] = $valValue')
						substituteDict = {'meterCofigKey': meterCofigKey, 'valKey': valKey, 'valValue': valValue}
						Error = Template.substitute(templateStr, substituteDict)
						Error += ', Unexpected Value. Expected Value: tuple of form <data, data type> from the range '
						templateStr = Template('$expectedValue')
						substituteDict = {'expectedValue': self.BlueprintMeterConfigDict['Values']}
						Error += Template.substitute(templateStr, substituteDict)
						log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
						raise RuntimeError, Error
			else:
				# ---------- Error ----------
				templateStr = Template('MeterConfigDict[$meterCofigKey] = $meterCofigValue')
				substituteDict = {'meterCofigKey': meterCofigKey, 'meterCofigValue': meterCofigValue}
				Error = Template.substitute(templateStr, substituteDict)
				Error += 'No implementation of SanityCheck for this Key!'
				log.error('CommunicationFrame :: SanityCheckMeterConfigDict() : Error = %s', Error)
				raise RuntimeError, Error
			
		log.info('CommunicationFrame :: SanityCheckMeterConfigDict() : OUT')

	def SanityCheckProtocolTemplateDict(self, ProtocolTemplateDict=None):
		log.info('CommunicationFrame :: SanityCheckProtocolTemplateDict() : IN')
		
		if not ProtocolTemplateDict:
			Error = 'ProtocolTemplateDict is None'
			log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
			raise RuntimeError, Error
			#pp.pprint(ProtocolTemplateDict)
		
		for cmdName, cmdData in ProtocolTemplateDict.iteritems():
			for cmdDataKey, cmdDataValue in cmdData.iteritems():
				
				#
				
				if cmdDataKey not in self.BlueprintProtocolTemplateDict.keys():
					# ---------- Error ----------
					templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey] = $cmdDataValue')
					substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'cmdDataValue': cmdDataValue}
					Error = Template.substitute(templateStr, substituteDict)
					templateStr = Template(', Unexpected Key. Expected Key: $expectedKey')
					substituteDict = {'expectedKey': self.BlueprintProtocolTemplateDict.keys()}
					Error += Template.substitute(templateStr, substituteDict)
					log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
					raise RuntimeError, Error
					
				#
				
				#
				
				if cmdDataKey in ['CmdInfo', 'SendDataStr']:
					if type(cmdDataValue) != str:
						# ---------- Error ----------
						templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey] = $cmdDataValue')
						substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'cmdDataValue': cmdDataValue}
						Error += ', Unexpected Value Type. Expected Value Type: str'
						log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
						raise RuntimeError, Error
				
				#
				
				elif cmdDataKey == 'SetUp':
					
					#
					
					if cmdDataValue == None:
						# ---------- Info ----------
						templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey] = $cmdDataValue')
						substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'cmdDataValue': cmdDataValue}
						Info = Template.substitute(templateStr, substituteDict)
						Info += ', Value Type is None.'
						log.info('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Info = %s', Info)
					
					#
					
					elif type(cmdDataValue) == dict:
						for setupKey, setupValue in cmdDataValue.iteritems():
							
							if setupKey not in self.BlueprintPortSetUp.keys():
								# ---------- Error ----------
								templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey][$setupKey]')
								substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'setupKey': setupKey}
								Error = Template.substitute(templateStr, substituteDict)
								templateStr = Template(', Unexpected Key. Expected Key: $expectedKey')
								substituteDict = {'expectedKey': self.BlueprintPortSetUp.keys()}
								Error += Template.substitute(templateStr, substituteDict)
								log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
								raise RuntimeError, Error
								
							# in order not to have big ranges in the Error Info string
							ErrorInfoData = self.BlueprintPortSetUp[setupKey]
							if type(ErrorInfoData) == tuple:
								(ErrorData, ErrorInfo) = ErrorInfoData
								ErrorInfoDataSubstituteDict = {'expectedValue': ErrorInfo}
							else:
								ErrorData = ErrorInfoData
								ErrorInfoDataSubstituteDict = {'expectedValue': ErrorInfoData}
								
							if setupValue == None:
								# ---------- Info ----------
								templateStr = Template(
									'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$setupKey] = $setupValue')
								substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'setupKey': setupKey,
												  'setupValue': setupValue}
								Info = Template.substitute(templateStr, substituteDict)
								Info += ', Value Type is None.'
								log.info('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Info = %s', Info)
							elif setupValue not in ErrorData:
								# ---------- Error ----------
								templateStr = Template(
									'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$setupKey] = $setupValue')
								substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'setupKey': setupKey,
												  'setupValue': setupValue}
								Error = Template.substitute(templateStr, substituteDict)
								templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
								Error += Template.substitute(templateStr, ErrorInfoDataSubstituteDict)
								log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
								raise RuntimeError, Error
					
					#
					
					else:
						# ---------- Error ----------
						templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey] = $cmdDataValue')
						substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'cmdDataValue': cmdDataValue}
						Error = Template.substitute(templateStr, substituteDict)
						Error += ', Unexpected Value Type. Expected Value Type: dict or None'
						log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
						raise RuntimeError, Error
				
				#
				
				elif cmdDataKey == 'ReceivedData':
					if type(cmdDataValue) == dict:
						for receivedDataKey, receivedDataValue in cmdDataValue.iteritems():
							if type(receivedDataKey) == tuple:
								(firs, second) = receivedDataKey
								try:
									(firs, second) > (0, 0)
									firs < second
								except:
									# ---------- Error ----------
									templateStr = Template(
										'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey]')
									substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
													  'cmdDataValue': cmdDataValue, 'receivedDataKey': receivedDataKey}
									Error = Template.substitute(templateStr, substituteDict)
									Error += ', Unexpected Key Value. Expected Key Value: tuple > the (0,0) and first < second.'
									log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s',
											  Error)
									raise RuntimeError, Error
							else:
								# ---------- Error ----------
								templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey]')
								substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
												  'cmdDataValue': cmdDataValue, 'receivedDataKey': receivedDataKey}
								Error = Template.substitute(templateStr, substituteDict)
								Error += ', Unexpected Key Type. Expected Key Type: tuple'
								log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
								raise RuntimeError, Error
								
							#
							
							if type(receivedDataValue) == str:
								if receivedDataValue not in self.BlueprintProtocolTemplateDict['ReceivedData']:
									# ---------- Error ----------
									templateStr = Template(
										'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey] = $receivedDataValue')
									substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
													  'cmdDataValue': cmdDataValue, 'receivedDataKey': receivedDataKey,
													  'receivedDataValue': receivedDataValue}
									Error = Template.substitute(templateStr, substituteDict)
									templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
									substituteDict = {
										'expectedValue': self.BlueprintProtocolTemplateDict['ReceivedData']}
									Error += Template.substitute(templateStr, substituteDict)
									log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s',
											  Error)
									raise RuntimeError, Error
							elif type(receivedDataValue) == tuple:
								(first, second) = receivedDataValue
								try:
									assert first in self.BlueprintProtocolTemplateDict['ReceivedData']
								except:
									# ---------- Error ----------
									templateStr = Template(
										'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey] = $receivedDataValue')
									substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
													  'cmdDataValue': cmdDataValue, 'receivedDataKey': receivedDataKey,
													  'receivedDataValue': receivedDataValue}
									Error = Template.substitute(templateStr, substituteDict)
									templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
									substituteDict = {
										'expectedValue': self.BlueprintProtocolTemplateDict['ReceivedData']}
									Error += Template.substitute(templateStr, substituteDict)
									log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s',
											  Error)
									raise RuntimeError, Error
							elif type(receivedDataValue) == dict:
								for receivedDataValueKey, receivedDataValueVal in receivedDataValue.iteritems():
									receivedDataValueKey = hexlify(receivedDataValueKey)
									if type(receivedDataValueVal) == str:
										# ---------- Error ----------
										templateStr = Template(
											'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey][$receivedDataValueKey] = $receivedDataValueVal')
										substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
														  'cmdDataValue': cmdDataValue,
														  'receivedDataKey': receivedDataKey,
														  'receivedDataValueKey': receivedDataValueKey,
														  'receivedDataValueVal': receivedDataValueVal}
										Error = Template.substitute(templateStr, substituteDict)
										templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
										substituteDict = {
											'expectedValue': self.BlueprintProtocolTemplateDict['ReceivedData']}
										Error += Template.substitute(templateStr, substituteDict)
										log.error(
											'CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s',
											Error)
										raise RuntimeError, Error
									elif type(receivedDataValueVal) == tuple:
										(first, second) = receivedDataValueVal
										try:
											assert first in self.BlueprintProtocolTemplateDict['ReceivedData']
										except:
											# ---------- Error ----------
											templateStr = Template(
												'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey][$receivedDataValueKey] = $receivedDataValueVal')
											substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
															  'cmdDataValue': cmdDataValue,
															  'receivedDataKey': receivedDataKey,
															  'receivedDataValueKey': receivedDataValueKey,
															  'receivedDataValueVal': receivedDataValueVal}
											Error = Template.substitute(templateStr, substituteDict)
											templateStr = Template(', Unexpected Value. Expected Value: $expectedValue')
											substituteDict = {
												'expectedValue': self.BlueprintProtocolTemplateDict['ReceivedData']}
											Error += Template.substitute(templateStr, substituteDict)
											log.error(
												'CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s',
												Error)
											raise RuntimeError, Error
									elif type(receivedDataValueVal) == dict:
										key = cmdName + ' | '
										key += cmdDataKey + ' | '
										(f, s) = receivedDataKey
										key += str(f) + ',' + str(s) + ' | '
										key += receivedDataValueKey
										self.SanityCheckProtocolTemplateDict({key: receivedDataValueVal})
									else:
										# ---------- Error ----------
										templateStr = Template(
											'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey][$receivedDataValueKey] = $receivedDataValue')
										substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
														  'cmdDataValue': cmdDataValue,
														  'receivedDataKey': receivedDataKey,
														  'receivedDataValueKey': receivedDataValueKey,
														  'receivedDataValue': receivedDataValue}
										Error = Template.substitute(templateStr, substituteDict)
										Error += ', Unexpected Key Type. Expected Key Type: str, tuple or dict'
										log.error(
											'CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s',
											Error)
										raise RuntimeError, Error
							else:
								# ---------- Error ----------
								templateStr = Template(
									'ProtocolTemplateFrame[$cmdName][$cmdDataKey][$receivedDataKey] = $receivedDataValue')
								substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey,
												  'cmdDataValue': cmdDataValue, 'receivedDataKey': receivedDataKey,
												  'receivedDataValue': receivedDataValue}
								Error = Template.substitute(templateStr, substituteDict)
								Error += ', Unexpected Key Type. Expected Key Type: str, tuple or dict'
								log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
								raise RuntimeError, Error
					else:
						# ---------- Error ----------
						templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey] = $cmdDataValue')
						substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'cmdDataValue': cmdDataValue}
						Error = Template.substitute(templateStr, substituteDict)
						Error += ', Unexpected Value Type. Expected Value Type: dict'
						log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
						raise RuntimeError, Error
				
				#
				
				else:
					# ---------- Error ----------
					templateStr = Template('ProtocolTemplateFrame[$cmdName][$cmdDataKey] = $cmdDataValue')
					substituteDict = {'cmdName': cmdName, 'cmdDataKey': cmdDataKey, 'cmdDataValue': cmdDataValue}
					Error = Template.substitute(templateStr, substituteDict)
					Error += 'No implementation of SanityCheck for this Key!'
					log.error('CommunicationFrame :: SanityCheckProtocolTemplateDict() : Error = %s', Error)
					raise RuntimeError, Error
			
		log.info('CommunicationFrame :: SanityCheckProtocolTemplateDict() : OUT')

	def YamlLoadDictionary(self, **kwargs):
		log.info('CommunicationFrame :: YamlLoadDictionary() : IN')
		

		# x= kwargs.get('123', None)
		# if not x:
		# 	Error = 'Load Path is Missing'
		# 	log.error('CommunicationFrame :: YamlLoadDictionary() : Error = %s', Error)
		# 	raise RuntimeError, Error

		try:
			path = kwargs['path']

		except:
			Error = 'Load Path is Missing'
			log.error('CommunicationFrame :: YamlLoadDictionary() : Error = %s', Error)
			raise RuntimeError, Error
			
		try:
			dictType = kwargs['dictType']
		except:
			Error = 'Load Dictionary Type is Missing'
			log.error('CommunicationFrame :: YamlLoadDictionary() : Error = %s', Error)
			raise RuntimeError, Error
			
		#loadStream = open(path, 'r')
		#YamlLoadDict = YamlLoad(loadStream)
		YamlLoadDict = LoadYamlConfig(path)
		#pp.pprint(YamlLoadDict)
		
		if dictType == 'MeterConfigDict':
			PostProcessMeterConfigDict = self.PostProcessYamlLoadMeterConfigDict(YamlLoadDict)
			
			try:
				meterName = kwargs['meterName']
			except:
				Error = 'Meter Name is Missing'
				log.error('CommunicationFrame :: YamlLoadDictionary() : Error = %s', Error)
				raise RuntimeError, Error
				
			RetLoadedDict = PostProcessMeterConfigDict[meterName]
		
		elif dictType == 'ProtocolTemplateDict':
			PostProcessProtocolTemplateDict = self.PostProcessYamlLoadProtocolTemplateDict(YamlLoadDict)
			RetLoadedDict = PostProcessProtocolTemplateDict
		
		else:
			Error = 'Load Dictionary Type is Unknown'
			log.error('CommunicationFrame :: YamlLoadDictionary() : Error = %s', Error)
			raise RuntimeError, Error
			
		log.info('CommunicationFrame :: YamlLoadDictionary() : OUT')
		return RetLoadedDict

	def PostProcessYamlLoadMeterConfigDict(self, YamlLoadedDict=None):
		log.info('CommunicationFrame :: PostProcessYamlLoadMeterConfigDict() : IN')
		
		if not YamlLoadedDict:
			Error = 'Meter Config Dictionary is None'
			log.error('CommunicationFrame :: PostProcessYamlLoadMeterConfigDict() : Error = %s', Error)
			raise RuntimeError, Error
			
		for meterName, meterConf in YamlLoadedDict.iteritems():
			for itemKey, itemValue in meterConf['Values'].iteritems():
				if type(itemValue) == str:
					try:
						(data, decoding) = itemValue.split(', ')
						assert data not in ['']
						assert decoding not in ['']
						assert decoding in self.BlueprintMeterConfigDict['Values']
						meterConf['Values'][itemKey] = (data, decoding)
					except:
						# ---------- Error ----------
						templateStr = Template('MeterConfigDict[$meterName][$itemKey] = $itemValue')
						substituteDict = {'meterName': meterName, 'itemKey': itemKey, 'itemValue': itemValue}
						Error = Template.substitute(templateStr, substituteDict)
						Error += ', Unexpected Value. Expected Value: string of form: <data><, ><decoding>'
						log.error('CommunicationFrame :: PostProcessYamlLoadMeterConfigDict() : Error = %s', Error)
						raise RuntimeError, Error
				else:
					# ---------- Error ----------
					templateStr = Template('MeterConfigDict[$meterName][$itemKey] = $itemValue')
					substituteDict = {'meterName': meterName, 'itemKey': itemKey, 'itemValue': itemValue}
					Error = Template.substitute(templateStr, substituteDict)
					Error += ', Unexpected Value Type. Expected Value Type: str'
					log.error('CommunicationFrame :: PostProcessYamlLoadMeterConfigDict() : Error = %s', Error)
					raise RuntimeError, Error
			
		log.info('CommunicationFrame :: PostProcessYamlLoadMeterConfigDict() : OUT')
		return YamlLoadedDict

	def PostProcessYamlLoadProtocolTemplateDict(self, YamlLoadedDict=None):
		log.info('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : IN')
		
		if not YamlLoadedDict:
			Error = 'Yaml Loaded Dictionary is None'
			log.error('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s', Error)
			raise RuntimeError, Error
			
		for cmdName, cmdData in YamlLoadedDict.iteritems():
			
			# ReceivedData
			
			tmpReceivedData = {}
			for instructionKey, instructionValue in cmdData['ReceivedData'].iteritems():
				
				# ReceivedData Key
				
				if type(instructionKey) == str:
					try:
						(baseStr, offsetStr) = instructionKey.split(',')
						baseStr != ''
						offsetStr != ''
						(baseInt, offsetInt) = (int(baseStr), int(offsetStr))
						instructionNewKey = (baseInt, offsetInt)
					except:
						# ---------- Error ----------
						templateStr = Template('ProtocolTemplateFrame[$cmdName][ReceivedData][$instructionKey]')
						substituteDict = {'cmdName': cmdName, 'instructionKey': instructionKey}
						Error = Template.substitute(templateStr, substituteDict)
						Error += ', Unexpected Key. Expected Key: string of form <value,value>'
						log.error('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s', Error)
						raise RuntimeError, Error
				else:
					# ---------- Error ----------
					templateStr = Template('ProtocolTemplateFrame[$cmdName][ReceivedData][$instructionKey]')
					substituteDict = {'cmdName': cmdName, 'instructionKey': instructionKey}
					Error = Template.substitute(templateStr, substituteDict)
					Error += ', Unexpected Key Type. Expected Key Type: str'
					log.error('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s', Error)
					raise RuntimeError, Error
					
				# ReceivedData Value
				
				if type(instructionValue) == str:
					try:
						try:
							(instruction, info) = instructionValue.split(', ')
						except:
							(instruction, info) = (instructionValue, '')
						assert instruction in self.BlueprintProtocolTemplateDict['ReceivedData']
						instructionNewValue = (instruction, info)
					except:
						# ---------- Error ----------
						templateStr = Template(
							'ProtocolTemplateFrame[$cmdName][ReceivedData][$instructionKey] = $instructionValue')
						substituteDict = {'cmdName': cmdName,
										  'instructionKey': instructionKey,
										  'instructionValue': instructionValue}
						Error = Template.substitute(templateStr, substituteDict)
						Error += ', Unexpected Value. Expected Value: string of form <instruction, info; PARAM_DDS_ID> or <instruction; PARAM_DDS_ID>'
						log.error('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s', Error)
						raise RuntimeError, Error
				elif type(instructionValue) == dict:
					instructionNewValue = {}
					for instructionValueKey, instructionValueVal in instructionValue.iteritems():
						
						#
						
						if type(instructionValueKey) == str:
							instructionNewValueKey = unhexlify(instructionValueKey)
						else:
							# ---------- Error ----------
							templateStr = Template(
								'ProtocolTemplateFrame[$cmdName][ReceivedData][$instructionKey][$instructionValueKey]')
							substituteDict = {'cmdName': cmdName,
											  'instructionKey': instructionKey,
											  'instructionValueKey': instructionValueKey}
							Error = Template.substitute(templateStr, substituteDict)
							Error += ', Unexpected Key Type. Expected Key Type: str'
							log.error('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s',
									  Error)
							raise RuntimeError, Error
							
						#
						
						if type(instructionValueVal) == str:
							try:
								try:
									(instruction, info) = instructionValueVal.split(',')
								except:
									(instruction, info) = (instructionValueVal, '')
								assert instruction in self.BlueprintProtocolTemplateDict['ReceivedData']
								instructionNewValue[instructionNewValueKey] = (instruction, info)
							except:
								# ---------- Error ----------
								templateStr = Template(
									'ProtocolTemplateFrame[$cmdName][ReceivedData][$instructionKey][$instructionValueKey] = $instructionValueVal')
								substituteDict = {'cmdName': cmdName,
												  'instructionKey': instructionKey,
												  'instructionValueKey': instructionValueKey,
												  'instructionValueVal': instructionValueVal}
								Error = Template.substitute(templateStr, substituteDict)
								Error += ', Unexpected Value. Expected Value: string of form <instruction,info> or <instruction>'
								log.error(
									'CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s',
									Error)
								raise RuntimeError, Error
						elif type(instructionValueVal) == dict:
							instructionNewValue[instructionNewValueKey] = self.PostProcessYamlLoadProtocolTemplateDict(
								{None: instructionValueVal})
						else:
							# ---------- Error ----------
							templateStr = Template(
								'ProtocolTemplateFrame[$cmdName][ReceivedData][$instructionKey][$instructionValueKey] = $instructionValueVal')
							substituteDict = {'cmdName': cmdName,
											  'instructionKey': instructionKey,
											  'instructionValueKey': instructionValueKey,
											  'instructionValueVal': instructionValueVal}
							Error = Template.substitute(templateStr, substituteDict)
							Error += ', Unexpected Value. Expected Value: str or dict'
							log.error('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s',
									  Error)
							raise RuntimeError, Error
							
							#
							
				else:
					# ---------- Error ----------
					templateStr = Template(
						'ProtocolTemplateFrame[$cmdName][ReceivedData][$instructionKey] = $instructionValue')
					substituteDict = {'cmdName': cmdName,
									  'instructionKey': instructionKey,
									  'instructionValue': instructionValue}
					Error = Template.substitute(templateStr, substituteDict)
					Error += ', Unexpected Value Type. Expected Value Type: str or dict'
					log.error('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : Error = %s', Error)
					raise RuntimeError, Error
					
				# modif ReceivedData
				
				tmpReceivedData[instructionNewKey] = instructionNewValue
				
			#
			
			cmdData['ReceivedData'] = tmpReceivedData
			
		#pp.pprint(YamlLoadedDict)
		if not cmdName:
			log.info('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : not cmdName')
			YamlLoadedDict = cmdData
			
		log.info('CommunicationFrame :: PostProcessYamlLoadProtocolTemplateDict() : OUT')
		return YamlLoadedDict

	def DictionaryTemplateSubstitute(self, *args, **kwargs):
		log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : IN')
		
		ProtocolFrameTemplateDict = {}
		MeterConfigDict = {}
		
		if 'ProtocolFrameTemplateDict' in kwargs:
			ProtocolFrameTemplateDict = kwargs['ProtocolFrameTemplateDict']
			log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : ProtocolFrameTemplateDict = kwargs[ProtocolFrameDict]')
		else:
			Error = 'Template Substitute is Missing the Protocol Frame Template Dictionary'
			log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
			raise RuntimeError, Error
			
		if 'MeterConfigDict' in kwargs:
			MeterConfigDict = kwargs['MeterConfigDict']
			log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : MeterConfigDict = kwargs[MeterConfigDict]')
		else:
			Error = 'Template Substitute is Missing the Meter Config Dictionary'
			log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
			raise RuntimeError, Error
			
		if 'cmdargs' in kwargs:
			cmdArgs = kwargs['cmdargs']
			log.info('GenericProtocolParser :: DictionaryTemplateSubstitute() : cmdArgs = %s', cmdArgs)
		else:
			cmdArgs = None
			log.info('GenericProtocolParser :: DictionaryTemplateSubstitute() : cmdArgs = %s', cmdArgs)
			
		if ProtocolFrameTemplateDict:
			log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : Protocol Frame Template Dictionary is OK')
		else:
			Error = 'Protocol Frame Template Dictionary is None or Empty'
			log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
			raise RuntimeError, Error
			
		if MeterConfigDict:
			log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : Meter Config Dictionary is OK')
		else:
			Error = 'Meter Config Dictionary is None or Empty'
			log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
			raise RuntimeError, Error
			
		SubstituteDict = MeterConfigDict['Values'].copy()
		
		#print 'cmdArgs: ', cmdArgs
		
		if cmdArgs:
			
			for valKey, valValue in cmdArgs.iteritems():
				try:
					assert type(valValue) == tuple
					(first, second) = valValue
					assert second in self.BlueprintMeterConfigDict['Values']
				except:
					# ---------- Error ----------
					templateStr = Template('cmdArgs[$valKey] = $valValue')
					substituteDict = {'valKey': valKey, 'valValue': valValue}
					Error = Template.substitute(templateStr, substituteDict)
					Error += ', Unexpected Value. Expected Value: tuple of form <data, data type> from the range '
					templateStr = Template('$expectedValue')
					substituteDict = {'expectedValue': self.BlueprintMeterConfigDict['Values']}
					Error += Template.substitute(templateStr, substituteDict)
					log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
					raise RuntimeError, Error
					
				if valKey in SubstituteDict.keys():
					# ---------- Info ----------
					templateStr = Template('cmdArgs[$valKey] = $valValue')
					substituteDict = {'valKey': valKey, 'valValue': valValue}
					Info += ' overwrite the Value in MeterConfigDict[Values].'
					Info = Template.substitute(templateStr, substituteDict)
					log.warning('CommunicationFrame :: DictionaryTemplateSubstitute() : Info = %s', Info)
					
				SubstituteDict[valKey] = valValue
			
		for item in SubstituteDict.iteritems():
			itemKey, (itemValue, itemEncoding) = item
			log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : Dencoding SubstituteDict[%s]', itemKey)
			
			# convert Value as Encoding to Value as hex
			
			if itemEncoding == 'Raw':
				SubstituteDict[itemKey] = itemValue
			
			elif itemEncoding == 'SingleDigitStr':
				SubstituteDict[itemKey] = ''
				for value in itemValue:
					SubstituteDict[itemKey] += '0' + value
			
			else:
				templateStr = Template('SubstituteDict[$itemKey]')
				substituteDict = {'itemKey': itemKey}
				Error = Template.substitute(templateStr, substituteDict)
				Error += ' is Missing Encoding Type'
				log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
				raise RuntimeError, Error
			
		crcStr = ''
		crcType = MeterConfigDict['Communication']['CRC']
		
		#print ProtocolFrameTemplateDict
		SendDataStr = ProtocolFrameTemplateDict['SendDataStr']
		ProtocolFrameTemplateDict['SendDataStr'] = ''
		
		if type(SendDataStr) == str:
			#print 'SendDataStr =', SendDataStr
			#print 'SendDataStrSplit =', SendDataStr.split(' ')
			for elementInSplited in SendDataStr.split(' '):
				#print 'elementInSplited =', elementInSplited
				if '$' in elementInSplited:
					
					templateStr = Template(elementInSplited)
					
					try:
						#print SubstituteDict
						substituteStr = Template.substitute(templateStr, SubstituteDict)
					except Exception, Error:
						# ---------- Error ----------
						templateStr = Template('Substitute is Missing a Value: $error')
						substituteDict = {'error': Error}
						Error = Template.substitute(templateStr, substituteDict)
						Error += 'Value must be in MeterConfigDict[Values] or as a Parameter'
						log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
						raise RuntimeError, Error
						
					crcStr += unhexlify(substituteStr)
				
				else:
					crcStr += unhexlify(elementInSplited)
		else:
			# ---------- Error ----------
			templateStr = Template('ProtocolFrameTemplateDict[SendDataStr] = $value')
			substituteDict = {'value': SendDataStr}
			Error = Template.substitute(templateStr, substituteDict)
			Error += ', Unexpected Value Type. Expected Value Type: str'
			log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
			raise RuntimeError, Error
			
		ProtocolFrameTemplateDict['SendDataStr'] = self.CRC(crcStr, crcType)
		
		CmdInfoStr = ProtocolFrameTemplateDict['CmdInfo']
		templateStr = Template(CmdInfoStr)
		try:
			ProtocolFrameTemplateDict['CmdInfo'] = Template.substitute(templateStr, SubstituteDict)
		except Exception, Error:
			# ---------- Error ----------
			templateStr = Template('Substitute is Missing a Value: $error')
			substituteDict = {'error': Error}
			Error = Template.substitute(templateStr, substituteDict)
			Error += 'Value must be in MeterConfigDict[Values] or as a Parameter'
			log.error('CommunicationFrame :: DictionaryTemplateSubstitute() : Error = %s', Error)
			raise RuntimeError, Error
			
		if ProtocolFrameTemplateDict['SetUp']:
			
			for itemKey, itemValue in MeterConfigDict['Connection']['SetUp'].iteritems():
				if itemKey not in ProtocolFrameTemplateDict['SetUp'].items():
					ProtocolFrameTemplateDict['SetUp'][itemKey] = itemValue
					log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : Sunbstituted ProtocolFrameTemplateDict[SetUp][%s]', itemKey)
				else:
					log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : NOT Sunbstituted ProtocolFrameTemplateDict[SetUp][%s]', itemKey)
		elif not ProtocolFrameTemplateDict['SetUp']:
			ProtocolFrameTemplateDict['SetUp'] = {}
			for itemKey, itemValue in MeterConfigDict['Connection']['SetUp'].iteritems():
				ProtocolFrameTemplateDict['SetUp'][itemKey] = itemValue
		else:
			log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : NOT Found ProtocolFrameTemplateDict[SetUp]')
		
		log.info('CommunicationFrame :: DictionaryTemplateSubstitute() : OUT')
		return (True, ProtocolFrameTemplateDict)

	def CRC(self, computeStr=None, crcType=None):
		log.info('CommunicationFrame :: CRC() : IN')
		
		if not computeStr:
			Error = 'Compute String is Missing'
			log.error('CommunicationFrame :: CRC() : Error = %s', Error)
			raise RuntimeError, Error
			
		if not crcType:
			Error = 'Compute CRC Type is Missing'
			log.error('CommunicationFrame :: CRC() : Error = %s', Error)
			raise RuntimeError, Error
		
		if crcType == 'CRC16_Modbus_LittleEndian':
			log.info('CommunicationFrame :: CRC() : Computing %s ', crcType)
			computeStr = CRC16().Calculate(endian='little', crctype='MODBUS', data=computeStr)
		elif crcType == 'CRC16_Modbus_BigEndian':
			log.info('CommunicationFrame :: CRC() : Computing %s ', crcType)
			computeStr = CRC16().Calculate(endian='big', crctype='MODBUS', data=computeStr)
		elif crcType == 'NO_CRC':
			log.info('CommunicationFrame :: CRC() : Computing %s ', crcType)
		elif crcType == '':
			log.info('CommunicationFrame :: CRC() : Computing %s ', crcType)
		else:
			Error = 'Compute CRC Type is Unknown'
			log.error('CommunicationFrame :: CRC() : Error = %s', Error)
			raise RuntimeError, Error
			
		log.info('CommunicationFrame :: CRC() : OUT')
		return computeStr

	# Interface Functions :
	def GetHelp(self, *args, **kwargs):
		log.info('CommunicationFrame :: GetHelp() : IN')
		
		log.info('CommunicationFrame :: GetHelp() : OUT')
		return None

	def GetMeterConfig(self, *args, **kwargs):
		log.info('CommunicationFrame :: GetMeterConfig() : IN')
		
		if not self.MeterConfigDict:
			Error = 'Meter Config Dict is Missing'
			log.error('CommunicationFrame :: GetMeterConfig() : Error = %s', Error)
			raise RuntimeError, Error
		else:
			RetMeterConfigDict = self.MeterConfigDict['Communication']
			RetMeterConfigDict['ConnType'] = self.MeterConfigDict['Connection']['Type']
			
		log.info('CommunicationFrame :: GetMeterConfig() : OUT')
		return RetMeterConfigDict

	def GetFrame(self, *args, **kwargs):
		log.info('CommunicationFrame :: GetFrame() : IN')
		
		FrameDict = None
		
		if 'framename' in kwargs:
			log.info('CommunicationFrame :: GetFrame() : Frame Dictionary obtained from kwargs[framename]')
			try:
				FrameDict = self.ProtocolTemplateDict[kwargs['framename']].copy()
			except Exception:
				Error = 'ProtocolTemplateDict is Missing CMD :', kwargs['framename']
				log.error('CommunicationFrame :: GetFrame() : Error = %s', Error)
				raise RuntimeError, Error
		else:
			log.info('CommunicationFrame :: GetFrame() : Frame Dictionary NOT obtained from kwargs[framename]')
			
		if 'frame' in kwargs:
			log.info('CommunicationFrame :: GetFrame() : Frame Dictionary obtained from kwargs[frame]')
			FrameDict = kwargs['frame'].copy()
		else:
			log.info('CommunicationFrame :: GetFrame() : Frame Dictionary NOT obtained from kwargs[frame]')
			
		if 'cmdargs' in kwargs:
			cmdArgs = kwargs['cmdargs']
			log.info('GenericProtocolParser :: GetFrame() : cmdArgs = %s', cmdArgs)
		else:
			cmdArgs = None
			log.info('GenericProtocolParser :: GetFrame() : cmdArgs = %s', cmdArgs)
			
		if not FrameDict:
			Error = 'Frame Dictionary Missing'
			log.error('CommunicationFrame :: GetFrame() : Error = %s', Error)
			raise RuntimeError, Error
			
		(State, FrameDict) = self.DictionaryTemplateSubstitute(
			ProtocolFrameTemplateDict=FrameDict,
			MeterConfigDict=self.MeterConfigDict,
			cmdargs=cmdArgs)
		
		if not State:
			Error = 'Template Substitute Fail'
			log.error('CommunicationFrame :: GetFrame() : Error = %s', Error)
			raise RuntimeError, Error
			
		log.info('CommunicationFrame :: GetFrame() : OUT')
		#pp.pprint(FrameDict)
		return FrameDict

def LoadYamlConfig(path):
    import yaml
    f = open(path)
    parsed_file = yaml.load(f)
    f.close
    return parsed_file

import logging as log
communicationFrame = CommunicationFrame(LoadSourceType="yaml", MeterName="meterName", MeterConfigPath="meterConfig.yaml", ProtocolTemplatePath="protocolTemplatePath.yaml")


