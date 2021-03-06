<?php

/**
 * @file
 * Provides the API key configuration form and validation routine
 */

/**
 * Implements hook_form();
 */
function sucuri_cloudproxy_config_form($form, &$form_state) {
    
  $form['key_configuration'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Key Configuration'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
  );
  $form['key_configuration']['sucuri_cloudproxy_site_key'] = array(
    '#type'          => 'textfield',
      '#title'         => t('Site Key'),
      '#default_value' => variable_get('sucuri_cloudproxy_site_key'),
      '#size'          => 32,
      '#maxlength'     => 32,
      '#description'   => t('The site key issued by Sucuri for this domain.'),
      '#required'      => TRUE,
      '#encrypt'       => TRUE,
  );
  $form['key_configuration']['sucuri_cloudproxy_secret_key'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Secret Key'),
    '#default_value' => variable_get('sucuri_cloudproxy_secret_key'),
    '#size'          => 32,
    '#maxlength'     => 32,
    '#description'   => t('The secret key issued by Sucuri for this domain.'),
    '#required'      => TRUE,
    '#encrypt'       => TRUE,
  );
 
  return system_settings_form($form);
}

/**
 * Implements hook_form_validate();
 */
function sucuri_cloudproxy_config_form_validate($form, &$form_state) {
  foreach (array(
    'sucuri_cloudproxy_site_key'   => 'site key',
    'sucuri_cloudproxy_secret_key' => 'secret key',
  ) as $k => $v) {

    if (!preg_match('/^[a-fA-F0-9]{32}$/', $form_state['values'][$k])) {
      form_set_error($k, t('Your @field should be a 32 character long hexadecimal string.', array('@field' => $v)));
    }
  }
}
