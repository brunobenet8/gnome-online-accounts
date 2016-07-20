/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/*
 * Copyright (C) 2011, 2012, 2014, 2015 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#if !defined (__GOA_BACKEND_INSIDE_GOA_BACKEND_H__) && !defined (GOA_BACKEND_COMPILATION)
#error "Only <goabackend/goabackend.h> can be included directly."
#endif

#ifndef __GOA_OAUTH2_PROVIDER_PRIV_H__
#define __GOA_OAUTH2_PROVIDER_PRIV_H__

#include <gio/gio.h>
#include <goabackend/goaoauth2provider.h>
#include <goabackend/goaprovider-priv.h>
#include <goabackend/goabackendtypes.h>
#include <webkitdom/webkitdom.h>

G_BEGIN_DECLS

/**
 * GoaOAuth2Provider:
 *
 * The #GoaOAuth2Provider structure contains only private data and should
 * only be accessed using the provided API.
 */
struct _GoaOAuth2Provider
{
  /*< private >*/
  GoaProvider parent_instance;
  GoaOAuth2ProviderPrivate *priv;
};

/**
 * GoaOAuth2ProviderClass:
 * @parent_class: The parent class.
 * @get_authorization_uri: Virtual function for goa_oauth2_provider_get_authorization_uri().
 * @get_token_uri: Virtual function for goa_oauth2_provider_get_token_uri().
 * @get_redirect_uri: Virtual function for goa_oauth2_provider_get_redirect_uri().
 * @get_scope: Virtual function for goa_oauth2_provider_get_scope().
 * @get_client_id: Virtual function for goa_oauth2_provider_get_client_id().
 * @get_client_secret: Virtual function for goa_oauth2_provider_get_client_secret().
 * @get_authentication_cookie: Virtual function for goa_oauth2_provider_get_authentication_cookie().
 * @get_identity_sync: Virtual function for goa_oauth2_provider_get_identity_sync().
 * @build_authorization_uri: Virtual function for goa_oauth2_provider_build_authorization_uri().
 * @get_use_mobile_browser: Virtual function for goa_oauth2_provider_get_use_mobile_browser().
 * @add_account_key_values: Virtual function for goa_oauth2_provider_add_account_key_values().
 * @process_redirect_url: Virtual function for goa_oauth2_provider_process_redirect_url().
 * @is_deny_node: Virtual function for goa_oauth2_provider_is_deny_node().
 * @is_identity_node: Virtual function for goa_oauth2_provider_is_identity_node().
 * @is_password_node: Virtual function for goa_oauth2_provider_is_password_node().
 *
 * Class structure for #GoaOAuth2Provider.
 */
struct _GoaOAuth2ProviderClass
{
  GoaProviderClass parent_class;

  /* pure virtual */
  const gchar *(*get_authorization_uri)        (GoaOAuth2Provider            *provider);
  const gchar *(*get_redirect_uri)             (GoaOAuth2Provider            *provider);
  const gchar *(*get_client_id)                (GoaOAuth2Provider            *provider);
  const gchar *(*get_client_secret)            (GoaOAuth2Provider            *provider);
  const gchar *(*get_authentication_cookie)    (GoaOAuth2Provider            *provider);
  gchar       *(*get_identity_sync)            (GoaOAuth2Provider            *provider,
                                                const gchar                  *access_token,
                                                gchar                       **out_presentation_identity,
                                                GCancellable                 *cancellable,
                                                GError                      **error);

  /* virtual but with default implementation */
  gchar       *(*build_authorization_uri)      (GoaOAuth2Provider            *provider,
                                                const gchar                  *authorization_uri,
                                                const gchar                  *escaped_redirect_uri,
                                                const gchar                  *escaped_client_id,
                                                const gchar                  *escaped_scope);
  const gchar *(*get_token_uri)                (GoaOAuth2Provider            *provider);
  const gchar *(*get_scope)                    (GoaOAuth2Provider            *provider);
  gboolean     (*get_use_mobile_browser)       (GoaOAuth2Provider            *provider);
  void         (*add_account_key_values)       (GoaOAuth2Provider            *provider,
                                                GVariantBuilder              *builder);

  /* pure virtual */
  gboolean     (*is_identity_node)             (GoaOAuth2Provider            *provider,
                                                WebKitDOMHTMLInputElement    *element);

  /* virtual but with default implementation */
  gboolean     (*is_deny_node)                 (GoaOAuth2Provider            *provider,
                                                WebKitDOMNode                *node);
  gboolean     (*is_password_node)             (GoaOAuth2Provider            *provider,
                                                WebKitDOMHTMLInputElement    *element);
  gboolean     (*process_redirect_url)         (GoaOAuth2Provider            *provider,
                                                const gchar                  *redirect_url,
                                                gchar                       **access_token,
                                                GError                      **error);


  /*< private >*/
  /* Padding for future expansion */
  gpointer goa_reserved[28];
};

G_END_DECLS

#endif /* __GOA_OAUTH2_PROVIDER_PRIV_H__ */
